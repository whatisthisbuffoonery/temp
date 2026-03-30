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
	else
		ft_putstr("NULL");
	ft_putchar('\n');
	free(buf);
}

void	me_handle_signals(int signo)
{
	if i()
		;
}

void	signal_init(struct sigaction *handler)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGQUIT);//one of these literally handles sigquit bruh
	handler[0].sa_mask = mask;
	handler[1].sa_mask = mask;
}

int main(void)
{
	char *buf;
	struct sigaction	handler[2];

	signal_init(handler);
	muh_number = 0;
	while (muh_number++ < 10)
	{
		buf = readline("I am a shell%");
		shell_print(buf);
	}
	(void) buf;
}
