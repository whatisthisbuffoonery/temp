#include "get_next_line.h"

char	*read_line(int fd, int *me_fd, char ***res)
{
	char	*a;

	if (!*res)
		*res = (2 * sizeof(char *));

char	*get_next_line(int fd)
{
	static char	**res;
	static int	me_fd;

	if (fd < 0)
		return (NULL);
	return (read_line(fd, &me_fd, &res));
}
