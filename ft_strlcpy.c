int	ft_strlcpy(char *dest, char *src, unsigned int dsize)
{
	unsigned int		i;
	unsigned int		min;
	unsigned int		ret;

	i = 0;
	min = dsize - 1;
	while (src[i])
		i ++;
	if (i < min)
		min = i;
	ret = i;
	i = 0;
	while (i < min)
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (ret);
}
