#include "header_mand.h"

//shove arg node in thru here

static char	*grab(t_queue *q, va_list *va)
{
	char	cmp;

//	if (!q->flags)
//		write(1, "NOO\n", 4);
//	else
//		write(1, "hm?\n", 4);
	if (q->type == str)
		return (q->str);
	else if (q->type == op)
	{
		cmp = q->arg;
		if (cmp == 'c')
			return (char_op(va_arg(*va, int), q));
		else if (cmp == 's' || cmp == 'p')
			return (ptr_op(va_arg(*va, uintptr_t), cmp, q));
		else if (cmp == 'd' || cmp == 'i')
			return (int_op(va_arg(*va, int), q));
		else if (cmp == 'u' || cmp == 'x' || cmp == 'X')
			return (uint_op(va_arg(*va, unsigned int), cmp, q));
		write(1, &cmp, 1);
		write(1, "	<--  who put this here\n", 25);
	}
	else
		write(1, "nil type in queue LO???\n", 25);
	return (NULL);
}

static int	print_strlen(char *a, t_queue *q)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i ++;
	if (q->arg == '0')
	{
		q->arg = 'c';
		i ++;
		while (a[i])
			i ++;
	}
	return (i);
}

static char	*print_strjoin(char *dst, char *src, t_queue *f, int *len)
{
	char	*ret;
	int		i;
	int		k;
	int		src_len;

	if (!dst || !src)
		return (NULL);//derail char op here. output of three nulls needs to show up as three nulls
	src_len = print_strlen(src, f);
	ret = malloc((*len + src_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < *len)
		ret[i] = dst[i];
	while (++k < src_len)
		ret[i + k] = src[k];
	ret[i + k] = '\0';
	if (f->type == op)
		free(src);
	*len += src_len;
	return (ret);
}

static void	*tantrum_boogaloo(char *new, char *tmp, t_queue *f)
{
	if (new && f->type == op)
		free(new);
	if (tmp)
		free(tmp);
	return (NULL);
}

char	*process(t_queue *q, va_list *va, int *len)
{
	t_queue	*f;
	char	*ret;
	char	*tmp;
	char	*new;

	f = q->next;
	ret = grab(q, va);
	if (!ret)
		return (NULL);
	*len = print_strlen(ret, q);
	while (f)
	{
		new = grab(f, va);
		tmp = print_strjoin(ret, new, f, len);
		if (ret != q->str)
			free(ret);
		if (!tmp || !new)
			return (tantrum_boogaloo(new, tmp, f));
		f = f->next;
		ret = tmp;
	}
	return (ret);
}
