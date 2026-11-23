#include <unistd.h>
#include <signal.h>
#include <stdio.h>//write not allowed
#include <stdbool.h>
#include <string.h>//error print
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

#define OK 1
#define BAD 0

volatile sig_atomic_t	signo;//only used for timeouts
int						timeout_bulb;//use a counter that doesnt update out of nowhere

void	sighands(int src)
{
	(void) src;
	//write(1, "ping\n", 5);
	signo = 1;
}

void	signal_init(void)
{
	struct sigaction	s;
	char				*ptr = (char *)&s;
	int					size = sizeof(s);
	int					i = 0;

	while (i < size)
		ptr[i++] = 0;
	s.sa_handler = sighands;
	sigemptyset(&s.sa_mask);
	sigaction(SIGALRM, &s, NULL);
}

void	sandbox_exit_verbose(int n, unsigned int timeout_src, int stop, int term)
{
	if (timeout_bulb)
		printf("Bad function: timed out after %d seconds\n", timeout_src);
	else if (term || stop)
		printf("Bad function: %s\n", strsignal(n));
	else if (n)
		printf("Bad function: exited with code %d\n", n);
	else
		printf("Nice function!\n");
}

int	sandbox_exit(int n, unsigned int timeout_src, bool verbose, pid_t pid)
{
	int	term = WIFSIGNALED(n);
	int	stop = WIFSTOPPED(n);

	if (signo)
	{
		//printf("attempt cleanup: %d...%d, %s\n", pid, kill(pid, SIGKILL), strerror(errno));
		kill(pid, SIGKILL);
		timeout_bulb = 1;
		n = 1;
	}
	else if (term)
		n = WTERMSIG(n);
	else if (stop)			//treat any stopped job as bad
		n = WSTOPSIG(n);	//example skipped verbose for stop signals and returned -1???
	else if (WIFEXITED(n))
		n = WEXITSTATUS(n);
	//printf("final exit status %d, stop %d term %d\n", n, stop, term);
	if (verbose)
		sandbox_exit_verbose(n, timeout_src, stop, term);
	if (!n)
		return (OK);
	return (BAD);
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid = fork();
	int		n;
	pid_t	waiting;

	signo = 0;
	timeout_bulb = 0;
	if (pid < 0)
		return (-1);
	if (!pid)
	{
		f();
		exit(0);
	}
	//printf("parent pid holding: %d\n", pid);
	signal_init();
	alarm(timeout);
	waiting = waitpid(pid, &n, WUNTRACED);
	while (waiting == -1 && errno == EINTR && !signo)
		waiting = waitpid(pid, &n, WUNTRACED);
	alarm(0);
	return (sandbox_exit(n, timeout, verbose, pid));
}

void ok_f(void)
{
	printf("noice. ");
}

void inf_f(void)
{
	while (1)
		;
}

void bad_exit(void)
{
	exit(41);
}

void suicide_f(void)
{
    kill(getpid(), SIGKILL);
    sleep(10);
}

void fast_print_f(void)
{
    printf("fast_print_f executed\n");
}

void abort_f(void)
{
    abort();
}

void stop_f(void)
{
    raise(SIGSTOP);
    sleep(10);
}

void segfault_f(void)
{
    int *p = NULL;
    *p = 42;
}

void cancel_alarm(void)
{
	struct sigaction ca;
	ca.sa_handler = SIG_IGN;
	sigaction(SIGALRM, &ca, NULL);

	sleep(5);
	printf("f waited 5 seconds, should be terminated before by alarm set in parent process if timeout < 5\n");
}

void leak_f(void)
{
	int *p = malloc(8);
	(void) p;
}

void test_func(void (*f)(void), unsigned int timeout, const char* name)
{
    printf("==== Test : %s (timeout %us) ====\n", name, timeout);
    int res = sandbox(f, timeout, true);
    printf("Result = %d\n\n", res);
}

int	main(void)
{
	test_func(ok_f, 2, "noice");
	test_func(fast_print_f, 2, "other ok func");
	test_func(abort_f, 2, "abort");
	test_func(stop_f, 2, "stop");
	test_func(segfault_f, 2, "segfault");
	test_func(cancel_alarm, 2, "chump thinks he can sleep");
	test_func(leak_f, 2, "leak func");
	test_func(inf_f, 2, "simple timeout");
	test_func(bad_exit, 2, "nonzero exit");
	test_func(suicide_f, 2, "SIGKILL self");
}
