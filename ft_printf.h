#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifdef BONUS
#  define BONUS 1
# endif
# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_flags
{
	char	minus_stack;
	char	plus_stack;
	char	dot;
	char	hash;
	char	type;
}			t_flags;

typedef struct s_tables
{
	unsigned char	type[256];
	unsigned char	bonus[256];
}					t_tables;

#endif
