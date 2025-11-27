#include "header_mand.h"

static void	type_bus(t_queue **q, char **dst, char type)//rename
{
	t_queue	*f;

	f = *q;
    *dst = NULL;
    if (!f)
        return ;
	*dst = malloc(2 * sizeof(char));//practice flags in strings
	if (!*dst)
		return ;//let caller clean up
	(*dst)[0] = type;
	(*dst)[1] = '\0';
}

static void	*tantrum(void **a, void **b)
{
	if (*a)
	{
		free(*a);
		*a = NULL;
	}
	if (*b)
	{
		free(*b);
		*b = NULL;
	}
    return (NULL);
}

t_queue	*op(const char *format, int *index)//no va yet
{
	t_queue	*ret;
	char	*res;//no flag needed hopefully

	*index += 2;//howd i forget the % that badly
	ret = q_new();
	type_bus(&ret, &res, format[1]);//i + 1
	if (!ret || !res)//practice putting types in strings for later
		return (tantrum(ret, res));
    ret->type = op;
    ret->str = res;
	return (ret);
}

t_queue	*str(const char *format, int start, int *end)
{
	int		i;
	int		flag;
	t_queue	*ret;
	char	*res;

	ret = q_new();
	flag = (format[*end] && format[*end + 1] == '%');
	*end += flag
	res = malloc(((start - *end) + 1) * sizeof(char));//stop before last relevant %
	i = -1;
    if (!ret || !res)
        return (tantrum(&ret, &res));
	while (start + ++i < *end)
		res[i] = format[i + start];
    res[i] = '\0';
	ret->str = res;
	*end += flag;//if double %, scan for more text
	ret->type = str;//whoop i forgot
	return (ret);
}