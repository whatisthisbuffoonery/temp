#include <unistd.h>
#include <stdarg.h>

void ft_putnbr(int n)
{
	char a;
	int t = 1;
	while (n / t > 9)
		t ++;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
}

void ft_putchar(unsigned int n)
{
	write(1, &n, 1);
}

void control(int a, int b, int c, int d)
{
	write(1, "control: ", 9);
	ft_putchar(a);
	ft_putchar(b);
	ft_putchar(c);
	ft_putchar(d);
	write(1, "\n", 1);
}

void test(int a, ...)
{
	va_list va;
	va_start(va, a);
	write(1, "test: ", 6);
	ft_putchar(a);
	ft_putchar(va_arg(va, int));
	ft_putchar(va_arg(va, int));
	ft_putchar(va_arg(va, int));
	write(1, "\n", 1);
}


int main(void)
{
	char a = '1';
	char b = '2';
	char c = '3';
	char d = '4';

	control(a, b, c, d);
	test(a, b, c, d);
}
