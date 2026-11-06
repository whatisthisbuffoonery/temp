#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

sig_atomic_t	signo = 0;

void	sighands(int n)
{
	if (n == SIGINT)
		signo = 128 + n;
}

int	bruh(void)
{
	while (!signo)
	{
		write(1, "bruh\n", 5);
		usleep(1e6);
	}
	return (0);
}

int	main(void)
{
	sigset_t			mask;
	struct sigaction	hands;

	sigemptyset(&mask);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGQUIT);
	memset(&hands, 0, sizeof(struct sigaction));
	hands = (struct sigaction){.sa_mask = mask, .sa_handler = sighands};
	sigaction(SIGINT, &hands, NULL);

	char	buf;
	pid_t	pid = fork();

	if (!pid)
		return (bruh());
	while (!signo && read(0, &buf, 1) > 0 && buf != '\n')
		continue ;
	if (!signo)
		kill(pid, SIGINT);
	waitpid(pid, NULL, 0);
}
