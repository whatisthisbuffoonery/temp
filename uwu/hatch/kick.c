#include <unistd.h>
#include <stdarg.h>

void ft_putnbr(int n)
{
	char a;
	int t = 1;
	while (n / t > 9)
		t *= 10;
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

void ft_putstr(char *a)
{
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
}

void control(char *a, int b, int c, int d)
{
//	(void) a;
//	(void) d;
//	(void) c;
	write(1, "control: ", 9);
	ft_putstr(a);
	ft_putnbr(b);
	ft_putnbr(c);
	ft_putchar(d);
	write(1, "\n", 1);
}

void test(char *a, ...)
{
	va_list va;
	va_start(va, a);
	write(1, "test: ", 6);
	ft_putstr(a);
	ft_putnbr(va_arg(va, int));
	ft_putnbr(va_arg(va, int));
	ft_putchar(va_arg(va, int));
	write(1, "\n", 1);
}


int main(void)
{
	char *a = "test";
	int b = 42;
	int c = 255;
	char d = '!';

	control(a, b, c, d);
	test(a, b, c, d);
}
