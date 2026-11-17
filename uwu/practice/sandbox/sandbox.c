#include <unistd.h>
#include <signal.h>
#include <stdio.h>//write not allowed
#include <stdbool.h>
#include <string.h>//error print

#define OK 1
#define BAD 0


sig_atomic_t signo;//only used for timeouts

void	sighands(int src)
{
	signo = 1;
}

int	sandbox_error(int n, bool verbose)
{
	char	*tmp;
	if (WIFSIGNALED(n))
	{
		n = WSI
		tmp = strsignal(n);
}

//handles parent errors and stop signals
int	no_verbose(void)
{
	return (-1);
}

void	signal_init(unsigned int tm)
{
	struct sigaction	s;
	char				*ptr = (char *)&s;
	int					size = sizeof(s);
	int					i = 0;

	while (i < size)
		ptr[i++] = 0;
	s.sa_handler = sighands;
	sigemptyset(&s.sa_mask);

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid = fork();

	signo = 0;
	if (pid < 0)
		return (no_verbose());
	if (!pid)
	{
		f();
		return (OK);//should setup timeout
	}
	signal_init(timeout);
	alarm(timeout);
	if (signo)
		return ();
	//wait
}
