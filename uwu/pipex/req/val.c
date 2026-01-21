#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char *a = malloc(2);
	char *b[5];
	b[0] = "ls";
	b[1] = "-nonsense";
	b[2] = NULL;
	pid_t fudge = fork();
	int fd2 = open("val.c", O_RDONLY);
	if (!fudge)
	{
		execve("/usr/bin/wls", b, NULL);
		//printf("%s\n", strerror(errno));
		perror(strerror(errno));
		free(a);
		write(1, "huh\n", 4);
		exit(0);
	}
	int fd = open("waku", O_RDONLY);
	close(fd2);
	close(0);
	close(1);
	close(2);
	(void) fd; (void) fd2;
//	waitpid(fudge, NULL, 0);
	wait(NULL);
	free(a);
}
