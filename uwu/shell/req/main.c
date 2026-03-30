#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

volatile sig_atomic_t	muh_number;

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
	free(buf);
}

void	me_handle_signals(int signo)
{
	muh_number = signo;
	if (muh_number == SIGQUIT)
		ft_putstr("\nsig quit received\n");
	else if (muh_number == SIGINT)
		ft_putstr("\nsig int received\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	muh_number = 0;
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
	struct sigaction	handler[2];
	struct sigaction	old[2];

	signal_init(handler);
	rl_catch_signals = 0;
	sigaction(SIGINT, &handler[0], &old[0]);
	sigaction(SIGQUIT, &handler[1], &old[1]);
	muh_number = 0;
	while (1)
	{
		buf = readline("I am a shell%");
		if (muh_number)
			free(buf);
		else
			shell_print(buf);
		if (!muh_number && !buf)
		{
			ft_putstr("exiting now\n");
			exit(0);
		}
		muh_number = 0;
	}
	(void) buf;
}
