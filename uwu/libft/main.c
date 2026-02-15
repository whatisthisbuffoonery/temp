#include "includes/libft.h"

void	printnstr(char *a, int len)
{
	write(1, a, len);
}

int main(void)
{
	char *src = "abc def ghi";
	char **a = ft_split(src, ' ');
	ft_putstr(src);
	write(1, "\n", 1);
	if (!a || !a[0] || !a[0][0])
		write(1, "fudge\n", 6);
	if (!a)
		return (1);
	ft_putnbr(ft_strlen(a[0]));
	write(1, "\n", 1);
	ft_putnbr(ft_strlen(a[1]));
	write(1, "\n", 1);
	ft_putnbr(ft_strlen(a[2]));
	write(1, "\n", 1);
	ft_putstr(a[0]);
	write(1, "\n", 1);
	ft_putstr(a[1]);
	write(1, "\n", 1);
	ft_putstr(a[2]);
	write(1, "\n", 1);
//	ft_putstr(a[3]);
	//if (!a[3])
	//	write(1, "\naa\n", 4);

	char *s = src;
	int i = 3;
	char c = ' ';
	if ((s[i] == c && s[i + 1] && s[i + 1] != c) || (!i && s[i] != c))
		ft_putstr("\nyes\n");
	else
		ft_putstr("\nno\n");

	free(a[0]);
	free(a[1]);
	free(a[2]);
	free(a);
}
