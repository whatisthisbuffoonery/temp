#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	char	table[128];

	i = 0;
	k = 0;
	while (i < 128)
		table[i++] = 0;
	i = 0;
	while (set[i])
		table[(unsigned char) set[i++]] = 1;
	i = 0;
	while (table[(unsigned char) s1[i]])
		i ++;
	while (s1[k])
		k ++;
	k --;
	while (table[(unsigned char) s1[k]])
		k --;
	return (ft_substr(s1, i, k - i));
}
