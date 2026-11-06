#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/select.h>
# include <errno.h>

# ifndef GNL_SIZE
#  define GNL_SIZE 128
# endif

# define GNL_CLEAR_ALL -42
# define GNL_STASH -1

typedef struct	s_string
{
	char			*s;
	struct s_string	*next;
	int				len;
}	t_string;

typedef struct	s_file
{
	char	buf[GNL_SIZE];
	int		fd;
	int		flags;
}	t_file;

char	*gnl(int fd);
char	***gnl_clear(int fd);

#endif
