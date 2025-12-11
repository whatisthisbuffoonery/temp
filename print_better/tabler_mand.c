void	tabler(char *type, char *flag, int *a, int *b)
{
	int	i;

	i = 0;
	*a = 0;
	*b = 0;
	while (i < 256)
	{
		type[i] = 0;
		flag[i++] = 0;
	}
	type['c'] = 1;
	type['s'] = 1;
	type['p'] = 1;
	type['d'] = 1;
	type['i'] = 1;
	type['u'] = 1;
	type['x'] = 1;
	type['X'] = 1;
}
