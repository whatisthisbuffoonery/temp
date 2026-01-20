#include "h_pipex.h"

int	main(int c, char **v)
{
	(void) c;
	(void) v;
	//if (c != 5)
	//	return (1);
	char *a = "/usr/bin/ls";
	char *a1 = "ls";
	char *b[3];
	b[2] = NULL;
	b[1] = "-l";
	b[0] = a1;
	execve(a, b, NULL);
	write(1, "poop\n", 5);
}
