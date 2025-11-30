#include <stdint.h>
#include <stdlib.h>

char	*char_op(unsigned int c)
{
	char	*ret;

	ret = malloc(2 * sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

static int	uint_help(char *ret, int flag, int *i)
{
	if (!ret)
		return (1);
	if (flag)
	{
		ret[0] = '0';
		ret[1] = 'x';
	}
	ret[*i + flag] = '\0';
	*i = flag;
	return (0);
}

char	*uint_op(uintptr_t n, char type)
{
	char			*ret;
	int				i;
	unsigned int	t;
	unsigned int	base;

	t = 1;
	i = 1;
	base = 16 - (6 * (type == 'u'));
	while (n / t >= base && ++i)
		t *= base;
	ret = malloc((i + 1 + (2 * (type == 'p'))) * sizeof(char));
	if (uint_help(ret, 2 * (type == 'p'), &i))
		return (NULL);
	while (t)
	{
		ret[i] = "0123456789abcdef"[((n / t) % base)];
		if (type == 'X' && ret[i] > '9')
			ret[i] -= 32;
		i ++;
		t /= base;
	}
	return (ret);
}

char	*int_op(long long n)
{
	char	*ret;
	int		i;
	int		t;
	int		flag;

	flag = (n < 0);
	t = 1;
	i = 1 + flag;
	if (n < 0)
		n = 0 - n;
	while (n / t >= 10 && ++i)
		t *= 10;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (flag)
		ret[0] = '-';
	ret[i] = '\0';
	i = flag;
	while (t)
	{
		ret[i++] = (((n / t) % 10) + '0');
		t /= 10;
	}
	return (ret);
}

char	*ptr_op(char *s, char type)
{
	int		i;
	char	*ret;

	if (!s)
		return (NULL);
	if (type == 'p')
		return (uint_op((uintptr_t) s, type));
	i = 0;
	while (s[i])
		i ++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}
