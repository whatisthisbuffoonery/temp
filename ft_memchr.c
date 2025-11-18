void	*ft_memchr(void *s, int c, unsigned int n)
{
	unsigned char	*a;
	unsigned int	i;

	i = 0;
	a = (unsigned char *) s;
	while (i < n && a[i] != c)
		i ++;
	if (a[i] == c)
		return ((void *) &a[i]);
	return (0);
}
