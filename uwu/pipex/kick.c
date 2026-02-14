#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	if (access(v[1], X_OK))
		printf("%s\n", (strerror(errno)));
	execve(v[1], &v[1], NULL);
	perror(NULL);
	perror("you");
}
