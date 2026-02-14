#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

int main(void)
{
	char *a = "/usr/bin/ls -l";
	char **b = ft_split(a, ' ');
	pid_t cpid = fork();

	if (!cpid)
	{
		execve(b[0], b, NULL);
		write(1, "\n\nnope\n\n", 8);
		exit(0);
	}
	else
		waitpid(cpid, NULL, 0);
	int i = 0;
	while (b[i])
		free(b[i++]);
	free(b);
	return (0);
}
