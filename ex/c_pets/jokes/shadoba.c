#include <stdio.h>

/*
   what in the fuck is cygames throwing at the wall this time
*/

int	bruh(void)
{
	char	buf[9] = "ETLMDPSS\0";
	int	i = 0;
	while (i < 8)
	{
		if (i < 4)
			buf[i] += 7;
		else
			buf[i] -= 7;
		if (buf[i] < 'A')
			buf[i] += 26;
		else if (buf[i] > 'Z')
			buf[i] -= 26;
		i ++;
	}
	printf("%s\n", buf);
	return (0);
}

int	main(int c, char **v)
{
	if (c < 2)
		return (bruh());
	int	i = 1;
	while (i < c)
		printf("%d\n", *v[i++] - 'A' + 1);
}
