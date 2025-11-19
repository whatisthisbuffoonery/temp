#include "libft.h"

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *s, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);

char	**ft_split(char const *s, char c);

//----

t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **lst, t_list *new);
int ft_lstsize(t_list *lst);
t_list *ft_lstlast(t_list *lst);
void ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstdelone(t_list *lst, void (*del)(void*));
void ft_lstclear(t_list **lst, void (*del)(void*));
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *));

void	ft_putnbr(int n)
{
	int 	t;
	char	a;

	t = 1;
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
	write(1, "\n", 1);
}

void	ft_putstr(char *a)
{
	if (!a)
		return ;
	int i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
	write(1, "\n", 1);
}

void	muh_putstr(void *a)
{
	ft_putstr((char *) a);
}

void	*muh_dup(void *a)
{
	return ((void *) ft_strdup((char *) a));
}

int		main(int c, char **v)
{
	/*
	if (ft_print('a'))
		write(1, "yes", 3);
	else
		write(1, "no", 2);
	*/
	char a[20];
//	a[4] = 'q';
//	int src = 4;
	/*
	char *b = &a[0];
	b = (char *)ft_memset(a, '1', 20);
	ft_memcpy(&b[src], "banana\0", 7);
	b = ft_memmove(&b[1], &b[src], 7);
	ft_putnbr(ft_strlen(b));
	return (0);
	*/
//	ft_bzero(a, 6);
	/*
	ft_putnbr(ft_strlcpy(a, "bab", 5));
	ft_putstr(a);
	ft_putnbr(ft_strlcat(a, "bobby", 5));
	ft_putstr(a);
	*/
	if (c < 2)
		return (1);
/*	
	char **arr = ft_split(v[1], 'a');
	int i = 0;
	if (!arr)
		write(1, "wtf\n", 4);
	else
	{
		while (arr[i])
		{
			ft_putstr(arr[i]);
			free(arr[i++]);
		}
		free(arr);
	}
*/	
/*
	char *test = ft_itoa(ft_atoi("   \r\r\t\n -1015a6"));
	ft_putstr(test);
	free(test);
*/

	//char s = *(char *) ft_memchr((void *) "abc", 'c', 3);
//	char *s = ft_strrchr("ab\0cdef", '\0');
//	ft_putstr(s + 1);

//	ft_putnbr(ft_strncmp("aaa", "aa", 99));
	int i = 1;
	t_list *dis = NULL;
	while (i < c - 1)
		ft_lstadd_front(&dis, ft_lstnew((void *) v[i++]));
	ft_lstadd_back(&dis, ft_lstnew((void *) v[i]));
	
	ft_putnbr(ft_lstsize(dis));
	write(1, "a\n", 2);
	ft_putstr((char *) ft_lstlast(dis)->content);
	t_list *deez = ft_lstmap(dis, muh_dup, free);
	ft_lstiter(dis, muh_putstr);
	ft_lstclear(&dis, free);
	ft_lstclear(&deez, free);
	(void) c;
	(void) v;
	(void) a;
	write(1, "\n", 1);
}
