#include "includes/libft.h"

int main(void)
{
	static unsigned char arr[20];

	*(unsigned int *) &arr[4] = 0xffffffff;
	int i = 0;
	while (i < 20)
	{
		ft_putnbr(arr[i++]);
		ft_putchar('\n');
	}
}
