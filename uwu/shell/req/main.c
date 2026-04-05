#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft.h"

volatile sig_atomic_t	muh_number;

void	do_thing(char *buf)
{
	char *arr[3];
	pid_t pid;

	(void) buf;
	ft_putstr("<thing> ");
	arr[0] = "/usr/bin/sleep";
	arr[1] = "3";
	arr[2] = NULL;
	pid = fork();
	if (!pid)
	{
		execve(arr[0], arr, NULL);
		perror("huh");
		exit(67);
	}
	/*
	while (w)
	{
		pid = wait(NULL);
		errno = 0;
		flag -= (pid < 0);
		if (flag)
		{
			ft_putnbr(pid);		//sig int causes this to immediately return -1
			ft_putchar('\n');
		}
		if (errno || pid < 0)
		{
			perror("error");
		}
	}
	*/
	while (waitpid(pid, NULL, 0) < 0);
	ft_putstr("done\n");
}

void	shell_print(char *buf)
{
	int i = 0;

	ft_putchar('|');
	while (buf && buf[i])
	{
		if (ft_isprint(buf[i]))
			ft_putchar(buf[i]);
		else
		{
			if (buf[i] == '\n')
				ft_putstr("\\n");
			else
				ft_putchar('.');
		}
		i ++;
	}
	ft_putchar('|');
	if (buf && buf[0])
		add_history(buf);
	else if (!buf)
		ft_putstr("NULL");
	ft_putchar('\n');
	if (buf && buf[0] == 's' && !buf[1])
		do_thing(buf);
	free(buf);
}

int	rl_handle_signals(void)//sigaction flag interrupt, rl handler	//does nl + redisplay (if not running a child)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (0);
}

void	me_handle_signals(int signo)
{
	muh_number = signo;
}

void	signal_init(struct sigaction *handler)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGQUIT);//one of these literally handles sigquit bruh
	handler[0].sa_mask = mask;
	handler[1].sa_mask = mask;

	handler[0].sa_handler = me_handle_signals;
	handler[1].sa_handler = me_handle_signals;
}



int main(void)
{
	char				*buf;
	struct sigaction	handler[2];//not needed
	struct sigaction	old[2];

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	ft_memset(&handler[0], 0, sizeof(struct sigaction));
	ft_memset(&handler[1], 0, sizeof(struct sigaction));
	signal_init(handler);
	rl_signal_event_hook = rl_handle_signals;
	sigaction(SIGINT, &handler[0], &old[0]);
	sigaction(SIGQUIT, &handler[1], &old[1]);
	muh_number = 0;
	while (1)
	{
		buf = readline("I am a shell% ");
//		if (muh_number)
//			free(buf);
//		else
		shell_print(buf);
		if (/*!muh_number &&*/ !buf)
		{
			ft_putstr("exiting now\n");
			rl_clear_history();
			exit(0);
		}
		muh_number = 0;
	}
	(void) buf;
}
