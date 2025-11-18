char	*ft_strnstr(char *hay, char *needle, unsigned int n)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	max;

	i = 0;
	k = 0;
	max = 0;
	while (needle && needle[max])
		max ++;
	n -= max;
	while (hay[i + k] && k < max && i < n)
	{
		if (hay[i + k] == needle[k])
		{
			k ++;
			continue ;
		}
		k = 0;
		i ++;
	}
	if (k == max)
		return (&hay[i]);
	return (0);
}
