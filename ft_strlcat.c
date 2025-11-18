int	ft_strlcat(char *dest, char *src, unsigned int dsize)
{
	unsigned int	i;
	unsigned int	k;
	int				ret;

	i = 0;
	k = 0;
	ret = 0;
	while (src[ret])
		ret ++;
	while (dest[i] && i < dsize)
		i ++;
	if (i == dsize)
		return (i + ret);
	dsize -= i + 1;
	while (k < dsize)
	{
		dest[i + k] = src[k];
		k ++;
	}
	dest[i + k] = '\0';
	return (ret + i);
}
