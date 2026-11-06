#include "gnl.h"

char	***gnl_clear(int fd)
{
	static char	*arr[FD_SETSIZE];
	int			i;

	if (fd == GNL_STASH)
		return (&arr);
	else if (fd > 0 && fd < FD_SETSIZE)
	{
		free(arr[fd]);
		arr[fd] = NULL;
		return (&arr);
	}
	i = 0;
	while (fd == GNL_CLEAR_ALL && i < FD_SETSIZE)
	{
		free(arr[i]);
		arr[i] = NULL;
		i ++;
	}
	return (&arr);
}

//caller will check errno for any mishaps
//set EINTR or EAGAIN to 1 to ignore them
char	*gnl_internal(t_file *file)
{
	static char	***arr;
	t_string	*str[2];
	int			stop;
	char		*ret;

	if (!arr)
		arr = gnl_clear(GNL_STASH);
	if (file->fd < 0 || file->fd > FD_SETSIZE)
		return ((errno = EINVAL), NULL);
	str[0] = NULL;
	ret = NULL;
	stop = -1;
	if (!make_string(&str[0], &stop, (*arr)[file->fd], *file))
		join_string(&ret, (*arr)[file->fd], str[0], stop);
	if (ret)
		stash_it(&(*arr)[file->fd], str[0], stop);
	while (str[0])
	{
		str[1] = str[0]->next;
		free(str[0]->s);
		free(str[0]);
		str[0] = str[1];
	}
	return (ret);
}

char	*gnl2(int fd, int flags)
{
	if (flags | EWOULDBLOCK)
		flags |= EAGAIN;
	return (gnl_internal((t_file){.fd = fd, .flags = flags}));
}

char	*gnl(int fd)
{
	return (gnl_internal((t_file){.fd = fd, .flags = 1}));
}
