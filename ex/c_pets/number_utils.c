#include "h_minirt.h"

int	max3_exp(int a, int b, int c)
{
	int	n;

	n = a;
	if (!n || (n < b && b))
		n = b;
	if (!n || (n < c && c))
		n = c;
	return (n);
}

int	min3_exp(int a, int b, int c)
{
	int	n;

	n = a;
	if (!n || (n > b && b))
		n = b;
	if (!n || (n > c && c))
		n = c;
	return (n);
}
