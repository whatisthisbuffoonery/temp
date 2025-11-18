#include <stdlib.h>

void	*ft_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned long	intmax;
	unsigned int	i;
	char			*ret;

	i = 0;
	intmax = 1;
	while (i++ < 32)
		intmax *= 2;
	intmax --;
	i = intmax / size;
	if (nmemb > i)
		return (0);
	size *= nmemb;
	ret = malloc(size);
	if (!ret)
		return (0);
	i = 0;
	while (i < size)
		ret[i++] = '\0';
	return ((void *) ret);
}
