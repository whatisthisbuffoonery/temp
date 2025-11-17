#include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_strlen(const char *s);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *s, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

void	ft_bzero(void *s, size_t n);

void	ft_putnbr(int n)
{
	int 	t;
	char	a;

	t = 1;
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + 48;
		write(1, &a, 1);
		t /= 10;
	}
}

int		main(void)
{
	/*
	if (ft_print('a'))
		write(1, "yes", 3);
	else
		write(1, "no", 2);
	*/
	char a[20];
	int src = 4;
	char *b = &a[0];
	b = (char *)ft_memset(a, '1', 20);
	//ft_bzero(&b[3], 6);
	ft_memcpy(&b[src], "banana\0", 7);
	b = ft_memmove(&b[1], &b[src], 7);
	ft_putnbr(ft_strlen(b));
	return (0);
}
