#include <unistd.h>

const char DIGIT_PAIRS[201] = 
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";

void	putnbr(int src)
{
	unsigned int	n;
	unsigned int	a;
	int				i;
	int				offset;
	char			buf[128];

	n = src;
	if (src < 0)
	{
		write(1, "-", 1);
		n = 0u - n;
	}
	i = 0;
	offset = 128 - 1;
	while (n >= 10)
	{
		a = (n % 100) * 2;
		buf[offset - i++] = DIGIT_PAIRS[a + 1];
		buf[offset - i++] = DIGIT_PAIRS[a];
		if (n < 100)
			break ;
		n /= 100;
	}
	if ((n && n < 10) || !i)
		buf[offset - i++] = n + '0';
	write(1, &buf[offset - (i - 1)], i);
	write(1, "\n", 1);
}

int	main(void)
{
//	printf("%lu, %lu, %lu, %lu, %lu, %lu, %lu\n", sizeof(short), sizeof(int), sizeof(long), sizeof(long long), sizeof(double), sizeof(long double), sizeof(__float128));
	putnbr(69420);
	putnbr(0);
	putnbr(1234);
	putnbr(-1000);
}
