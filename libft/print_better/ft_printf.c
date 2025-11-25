/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 02:17:50 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/26 06:12:51 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	tantrum(void **a, void **b)
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
}

static void	type_bus(t_queue **q, char **dst, char type)
{
	t_queue	*f;

	f = *q;
	f->type = op;
	*dst = malloc(2 * sizeof(char));//practice flags in strings
	if (!*dst)
		return ;//let caller clean up
	(*dst)[0] = type;
	(*dst)[1] = '\0';
	f->str = *dst;//i fuggin forgot
}

static void	*clear_q(t_queue **q)
{
	t_queue	*f;
	t_queue *tmp;

	f = *q;
	while (f)
	{
		tmp = f->next;
		if (f->str)//mmmmm
			free(f->str);
		free(f);
		f = tmp;
	}
	return (NULL);
}

static t_queue	q_new(void)
{
	t_queue	*tmp;

	tmp = malloc(sizeof(t_queue));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->str = NULL;
	return (tmp);
}

static t_queue	*op(const char *format, int *index, char *table)//no va yet
{
	int		i;
	t_queue	*ret;
	char	*res;//no flag needed hopefully

	i = 0;
	*index += 1;//howd i forget the % that badly
	ret = q_new();
	if (!ret || !table[(unsigned char) format[*index]])//start and end should be the same by now
		return (tantrum(ret, 0));
	type_bus(&ret, &res, format[i++]);//i++ to get off the type specifier dumbass
	if (!ret || !res)//practice putting types in strings for later
		return (tantrum(ret, res));
	return (ret);
}

static t_queue	*str(const char *format, int start, int *end)
{
	int		i;
	int		flag;
	t_queue	*ret;
	char	*res;

	ret = q_new();//q_new caller 1
	flag = (format[*end + 1] == '%');
	*end += flag
	res = malloc(((*start - *end) + 1) * sizeof(char));//stop before last relevant %
	i = -1;
	while (ret && res && start + ++i < *end)
		res[i] = format[i + start];
	if (ret && res)
		ret->str = res;
	else
		return (tantrum(&ret, &res));//free and set to null on failure
	*end += flag;//if double %, scan for more text
	ret->type = str;//whoop i forgot
	return (ret);
}

static void	enq(t_queue **q, t_queue *tmp)
{
	t_queue	*f;
	if (!tmp)//on any bad input
	{
		clear_q(q);
		return ;
	}
	if (!*q)
	{
		*q = tmp;
		return ;
	}
	f = *q;
	while (f->next)
		f = f->next;
	f->next = tmp;
}

static void	tabler(char *table, int *a, int *b)
{
	int	i;

	i = 0;
	*a = 0;
	*b = 0;
	while (i < 256)
		table[i++] = 0;
	table['c'] = 1;
	table['s'] = 1;
	table['p'] = 1;
	table['i'] = 1;
	table['u'] = 1;
	table['x'] = 1;
	table['X'] = 1;
}

static void	tokens(const char *format, t_queue **q)
{
	int		i;
	int		start;
	char	table[256];
	t_queue	*tmp;

	tabler(table, &i, &start);
	while (format[i])
	{
		while (format[i] && format[i] != '%')
			i ++;
		if (format[start] == '%')//no start + 1 guard
			tmp = op(format, start, &i);//tmp null
		else if (format[start])
			tmp = str(format, &i, table);//tmp null
		enq(q, tmp);//signals q null, tmp->next = null
		start = i;//both funcs edit i to be either a % or outside an arg// explicit bomb out on no match
		if (!tmp)
			return ;//clear again...?
	}
}

static char	*process(t_queue *q, va_list va)
{
	dd;
}

int	ft_printf(const char *format, ...)//actual string production TBA
{
	va_list	va;
	char	*ret;
	t_queue *q;

	q = NULL;
	ret = NULL;
	va_start(va, format);
	tokens(format, &q);//signal: q == null
	if (q)
	{
		ret = process(q, va);
		clear_q(q);
	}
	va_end(va);
	return (!ret);
}
