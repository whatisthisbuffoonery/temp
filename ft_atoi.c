int	ft_atoi(char *src)
{
	int	i;
	int	a;
	int	flag;

	i = 0;
	a = 0;
	flag = 1;
	while (src[i] == ' ' || (src[i] >= '\t' && src[i] <= '\r'))
		i ++;
	if (src[i] == '-' || src[i] == '+')
	{
		if (src[i] == '-')
			flag = -1;
		i ++;
	}
	while (src[i] >= '0' && src[i] <= '9')
	{
		a *= 10;
		a += src[i] - '0';
		i ++;
	}
	return (a * flag);
}
