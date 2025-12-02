#include "header_mand.h"

int	type_bus(t_queue **q, const char *format, char *type);

static void	*tantrum(t_queue **a, char **b)
{
	if (*a)
	{
		free(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free(*b);
		*b = NULL;
	}
	return (NULL);
}

t_queue	*new_op(const char *format, int *index, char *type)//no va yet
{
	t_queue	*ret;

	ret = q_new();
	*index += 1 + type_bus(&ret, &format[1], type);//i + 1// motherf i need to squeeze in 'type' here
	if (!ret || !ret->arg)
		return (tantrum(&ret, NULL));
	ret->type = op;
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
