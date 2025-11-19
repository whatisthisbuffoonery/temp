#include <stdlib.h>
void	ft_putstr(char *a);
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ret;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i ++;
	if (start > i)
		len = 0;
	if (start + len >= i)
		len = i - start;
	ret = malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (0);
//	ft_putstr();
	i = 0;
	while (i < len)
	{
		ret[i] = s[i + start];
		i ++;
	}
	ret[i] = '\0';
//	ft_putstr(ret);
	return (ret);
}
