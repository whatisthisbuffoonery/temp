#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

void	ft_putstr(char *a);

void	ft_putnbr(int n);

static int	err2_help(char const *s)
{
	if (!s || !s[0])
		return (1);
	return (0);
}

static int	while_help(char const *s, char c, int *index, int *zero)
{
	int	i;

	i = *index;
	if (err2_help(s))
		return (0);
	if (*zero)
	{
		i ++;
		*zero = 0;
	}
	while (s[i] && s[i + 1])
	{
		if ((s[i] == c && s[i + 1] && s[i + 1] != c) || (!i && s[i] != c))
		{
			*zero = !i;
			i += (s[i] == c);
			*index = i;
			return (1);
		}
		i ++;
	}
	return (0);
}

static void	var_help(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static int	err_help(char **ret, int count)
{
	if (!ret)
		return (1);
	if (!count)
	{
		ret[0] = 0;
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		zero;
	int		count;
	char	**ret;

	var_help(&i, &count, &zero);
	while (while_help(s, c, &i, &zero))
		count ++;
	ret = malloc((count + 1) * sizeof(char *));
	if (err_help(ret, count))
		return (ret);
	var_help(&i, &count, &k);
	while (while_help(s, c, &i, &k))
	{
		k = i;
		while (s[k] && s[k] != c)
			k ++;
		ret[count] = ft_substr(s, i, k - i);
		if (!(ret[count++]))
			return (0);
	}
	ret[count] = 0;
	return (ret);
}
