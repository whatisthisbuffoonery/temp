int	ft_memcmp(void *s1, void *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (i < n && a[i] == b[i])
		i ++;
	return (a[i] - b[i]);
}
