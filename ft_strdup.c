#include <stdlib.h>

char	*ft_strdup(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i])
		i ++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}
