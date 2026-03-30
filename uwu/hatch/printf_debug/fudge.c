#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

void	ft_putnbr_long(void *num)
{
	char a;
	unsigned long n = (unsigned long) num;
	long t = 1;
	while (t && n / t > 15)
		t *= 16;
	while (t)
	{
		a = ((n / t) % 16) + '0';
		if (a > '9')
			a += ('a' - '0') - 10;
		write(1, &a, 1);
		t /= 16;
	}
	write(1, "\n", 1);
}

void	ft_putnbr(unsigned long n)
{
	char a;
	unsigned long long t = 1;
	while (t && n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
	write(1, "\n", 1);
}

void	wrapper(int a, ...)
{
	va_list va;
	va_start(va, a);
	ft_putnbr_long(va_arg(va, void *));
	va_end(va);
	(void) a;
}

void	chocolate(void)
{
	unsigned long n = ULONG_MAX;
	unsigned long t = 1;
	char a;

	while (n / t > 15)
		t *= 16;
	a = ((n / t) % 16);
	if (a < 10)
		a += '0';
	else
		a += 'a' - 10;
	write(1, &a, 1);
	write(1, "\n", 1);
	if (t == n)
		write(1, "eh?\n", 4);
	ft_putnbr(n);
	ft_putnbr(t);
	ft_putnbr(n / t);
	printf("%llu, %llu, %llu, %llu\n", 18446744073709551616ULL, 1152921504606846976ULL, 18446744073709551616ULL / 1152921504606846976ULL, 18446744073709551616ULL / 18446744073709551616ULL);
//	ft_putnbr(160 / 10);
}

int main(void)
{
	char *a;
	a = "lel";
	(void) a;
	chocolate();
//	wrapper(0, LONG_MAX);
//	printf("%#x", LONG_MAX);
//	printf("%#x", UINT_MAX);
}
