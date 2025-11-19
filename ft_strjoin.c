#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	char	*ret;

	a = 0;
	b = 0;
	while (s1[a])
		a ++;
	while (s2[b])
		b ++;
	ret = malloc((a + b + 1) * sizeof(char));
	if (!ret)
		return (0);
	a = -1;
	while (s1[++a])
		ret[a] = s1[a];
	b = -1;
	while (s2[++b])
		ret[a + b] = s2[b];
	ret[a + b] = '\0';
	return (ret);
}
