#include "gnl.h"

int	add_string(t_string **dst, char *buf, int len)
{
	t_string	*add;
	t_string	*tail;

	if (len < 1)
		return (0);
	add = malloc(sizeof(t_string));
	if (add)
		add->s = malloc(sizeof(char) * (len + 1));
	if (!add || !add->s)
		return ((free(add)), 1);
	i = -1;
	while (++i < len)
		add->s[i] = buf[i];
	add->s[i] = '\0';
	add->len = len;
	add->next = NULL;
	tail = *dst;
	while (tail && tail->next)
		tail = tail->next;
	if (tail)
		tail->next = add;
	else
		*dst = add;
	return (0);
}

int	read_error(int len, int flags)
{
	if (len >= 0)
		return (0);
	else if (errno == EINTR && !(flags | EINTR))
		return (1);
	return ((errno == EAGAIN || errno == EWOULDBLOCK) && !(flags | EAGAIN));
}

int	make_string(t_string **dst, int *stop, char *stash, t_file file)
{
	int			i[2];
	t_string	*curr;

	i[1] = 0;
	while (stash && stash[i[1]])
		i[1] ++;
	if (add_string(dst, stash, i[1]))
		return (1);
	while (1)
	{
		i[0] = 0;
		while (i[0] < i[1])
		{
			if (buf[i[0]] == '\n')
				return ((*stop = i[0]), 0);
			i[0] ++;
		}
		errno = 0;
		i[1] = read(file.fd, file.buf, GNL_SIZE);
		if (read_error(i[1], file.flags) || add_string(dst, file.buf, i[1]))
			return (1);
		if (!i[1])
			break ;
	}
	return (0);
}

int dst_start(char **dst, t_string *src, int stop)
{
	int	len;

	len = 0;
	while (src && src->next)
	{
		len += src->len;
		src = src->next;
	}
	if (stop < 0)
		len += src->len;
	else
		len += stop + (stop >= 0);
	if (len > 0)
		*dst = malloc(sizeof(char) * (len + 1));
	return (!*dst);
}

void	join_string(char **dst, char *stash, t_string *src, int stop)
{
	int	i;
	int	len;

	len = 0;
	if (dst_start(dst, stash, src, stop))
		return ;
	while (src && src->next)
	{
		i = 0;
		while (src->s[i])
			(*dst)[len++] = src->s[i++];
		src = src->next;
	}
	i = 0;
	while ((stop < 0 && i < src->len) || (stop >= 0 && i < stop))
		(*dst)[len++] = src->s[i++];
	if (stop >= 0)
		(*dst)[len++] = '\n';
	(*dst)[len] = '\0';
}
