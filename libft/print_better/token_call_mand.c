#include "header_mand.h"

int	type_bus(t_queue **q, char **dst, const char *format);

static void	*tantrum(t_queue **a, char **b)
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

t_queue	*new_op(const char *format, int *index)//no va yet
{
	t_queue	*ret;
	char	*res;//no flag needed hopefully

	ret = q_new();
	*index += 1 + type_bus(&ret, &res, &format[1]);//i + 1
	if (!ret || !res)//practice putting types in strings for later
		return (tantrum(&ret, &res));
	ret->type = op;
	ret->str = res;
	return (ret);
}

t_queue	*new_str(const char *format, int start, int *end)
{
	int		i;
	int		flag;
	t_queue	*ret;
	char	*res;

	ret = q_new();
	flag = (format[*end] && format[*end + 1] == '%');
	*end += flag;
	res = malloc(((*end - start) + 1) * sizeof(char));//stop before last relevant %
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
