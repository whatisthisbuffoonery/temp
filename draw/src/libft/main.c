#include "includes/libft.h"

int main(void)
{
	char *c = "1,0x810202";
	int i = 0;
	ft_putnbr(ft_atohu_ind(c, &i, 4));
	ft_putchar('\n');
	ft_putnbr(0x810202);
	ft_putchar('\n');
	if (i != (int) ft_strlen(c))
		ft_putstr("\nerr\n");
	ft_putnbr(i);
	ft_putchar('\n');
	ft_putnbr(ft_strlen(c));
	ft_putchar('\n');
}
