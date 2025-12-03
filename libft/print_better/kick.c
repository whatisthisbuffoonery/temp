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

void control(int a, int b, int c, int d)
{
	write(1, "control: ", 9);
	ft_putnbr(a);
	ft_putnbr(b);
	ft_putnbr(c);
	ft_putnbr(d);
	write(1, "\n", 1);
}

void test(int a, ...)
{
	va_list va;
	va_start(va, a);
	write(1, "test: ", 6);
	ft_putnbr(a);
	ft_putnbr(va_arg(va, int));
	ft_putnbr(va_arg(va, int));
	ft_putnbr(va_arg(va, int));
	write(1, "\n", 1);
}


int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	control(a, b, c, d);
	test(a, b, c, d);
}
