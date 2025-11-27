void	tabler(char *table, int *a, int *b)
{
	int	i;

	i = 0;
	*a = 0;
	*b = 0;
	while (i < 256)
		table[i++] = 0;
	table['c'] = 1;
	table['s'] = 1;
	table['p'] = 1;
	table['i'] = 1;
	table['u'] = 1;
	table['x'] = 1;
	table['X'] = 1;
}