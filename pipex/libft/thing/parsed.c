#include "libft.h"

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	char **a = parsed_argsplit(v[1]);
	int i = 0;
	if (a)
	{
		while (a[i])
		{
			ft_putstr("str__:");
			ft_putstr(a[i]);
			ft_putstr("\n");
			free(a[i++]);
		}
		ft_putstr("\nmain: ");
		ft_putnbr(i);
		ft_putstr("\n");
	}
	else
		ft_putstr("\nwtf\n");
	free(a);
}
