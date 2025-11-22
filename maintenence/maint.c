#include "libft.h"

int	ft_isalpha(int c);

void ft_putnbr(int n)
{
	char a;
	int t = 1;
	if (n < 0)
	{
		write(1, "-", 1);
		n = 0 - n;
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + 48;
		write(1, &a, 1);
		t /= 10;
	}
}

void ft_putstr(char *a)
{
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
}

void probe(char *a, int n)
{
	ft_putstr(a);
	ft_putnbr(n);
	write(1, "\n", 1);
}

void ft_memwrite(char *a, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		if (!a[i])
			write(1, ".", 1);
		else
			write(1, &a[i], 1);
		i ++;
	}
}

int main(void)
{
//	char a1[30];
//	char a2[30];
//	ft_memset(a1, '1', 30);
//	ft_memset(a2, '1', 30);
	/*
	char *a = ft_memcpy(a1, "a\0", 2);
	char *b = ft_memcpy(a1 + 5, "b\0", 2);
	char *c = ft_memcpy(a2, "c\0", 2);
	char *d = ft_memcpy(a2 + 5, "d\0", 2);
	*/
	char *a = "a\0";
	char *b = "b\0";
	char *c = "c\0";
	char *d = "d\0";
	t_list *l1 = 0;
	t_list *l2 = 0;
	ft_lstadd_back(&l1, ft_lstnew(a));
	ft_lstadd_back(&l1, ft_lstnew(b));
	ft_lstadd_back(&l2, ft_lstnew(c));
	ft_lstadd_back(&l2, ft_lstnew(d));

	ft_lstadd_back(&l1, l2);

	ft_putstr((char *) l1->content);
	ft_putstr("\n");
	ft_putstr((char *) l1->next->content);
	ft_putstr("\n");
//	ft_putstr((char *) l2->content);
	ft_putstr((char *) l1->next->next->content);
	ft_putstr("\n");
	ft_putstr((char *) l1->next->next->next->content);
//	ft_putstr((char *) l2->next->content);
//	ft_putstr("\n");

	ft_lstclear(&l1, 0);

//	ft_memwrite(a1, 30);
//	ft_putstr("\n");
//	ft_memwrite(a2, 30);
//	ft_putstr("\n");
	//ft_putstr(a);
	write(1, "\n", 1);
}
