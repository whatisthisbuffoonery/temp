char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i ++;
	if (s[i] == c)
		return (&s[i]);
	return (0);
}
