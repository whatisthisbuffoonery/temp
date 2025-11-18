char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i ++;
	while (i && s[i] != c)
		i --;
	if (s[i] == c)
		return (&s[i]);
	return (0);
}
