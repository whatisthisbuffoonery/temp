

#include "libft.h"
//no negatives
unsigned int	ft_atohu_ind(char *s, int *index, int i)
{
	unsigned int	a;

	a = 0;
	while (ft_ishex(s[i]))
	{
		a *= 16;
		a += (s[i] >= 'a') * (s[i] - ('a' - 10));
		a += (s[i] >= 'A' && s[i] <= 'Z') * (s[i] - ('A' - 10));
		a += (s[i] >= '0' && s[i] <= '9') * (s[i] - '0');
		i ++;
	}
	*index += i;
	return (a);
}
