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
	int		width;
	int		precision;
	char	zero;
	char	dash;
	char	hex;
	char	space;
	char	plus;
	char	w_set;
	char	p_set;
}	t_pf_specifiers;

typedef struct s_write_head
{
	t_pf_specifiers	sp;
	va_list			*va;
	char			*buf;
	char			*fer;
	int				fd;
	int				flags;
	int				minus;
	const char		*thing;
}	t_write_head;

/*
	const char		pairs[] = 
		"0001020304050607080910111213141516171819"
		"2021222324252627282930313233343536373839"
		"4041424344454647484950515253545556575859"
		"6061626364656667686970717273747576777879"
		"8081828384858687888990919293949596979899";
*/
int	ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));

/*internal only*/
int	printf_write(t_write_head w, const char *str, int len);
int	printf_repeat_write(t_write_head w, char c, int len);
int	fill_width(t_write_head w, int buflen, int p);
int	fill_precision(t_write_head w, int p);
int	fill_precision_hex(t_write_head w, int p);
int	printf_max(int a, int b);

#endif
