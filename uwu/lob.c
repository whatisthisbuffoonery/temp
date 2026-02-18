#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void ft_putnbr(unsigned long n)
{
	unsigned long t = 1;
	char a;

	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
	write(1, "\n", 1);
}

int main(void)
{
	//char *a = malloc(1);
	//free(a);
	//ft_putnbr((unsigned long) a);
	printf("%s\n", strerror(ENOEXEC));
}
