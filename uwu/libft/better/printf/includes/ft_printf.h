#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"
# include <stdio.h>

# define PRINTF_PROBE -1
# define PF_EAGAIN 1
# define PF_EINTR 2

# define NUM_BUFFER 256

typedef struct s_pf_specifiers
{
	char	zero;
	char	dash;
	char	hex;
	char	space;
	char	plus;
	char	width;
	char	precision;
	char	w_set;
	char	p_set;
}	t_pf_specifiers;

typedef struct s_write_head
{
	t_pf_specifiers	sp;
	va_list			*va;
	char			*buf;
	int				fd;
	int				flags;
	int				minus;
}	t_write_head;

int	ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));

/*internal only*/
int	printf_write(t_write_head w, const char *str, int len);
int	printf_repeat_write(t_write_head w, char c, int len);
int	fill_width(t_write_head w, int buflen, int p);
int	fill_precision(t_write_head w, int p);
int	fill_precision_hex(t_write_head w, int p);

#endif
