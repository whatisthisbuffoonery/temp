#include "h_pipex.h"

//i == 1 condition to change, rest is ok
//oh my fu I need a new strncmp //then: new read for partial reads and not count \n for limiter
//new loop for partial reads
//!!pipex uses > TRUNC without heredoc and >> no TRUNC with heredoc
//heredoc reports its


int	ffd_start(char **v, int *i)
{
	int	newfd;

	errno = 0;
	newfd = open(v[1], O_RDONLY);
	while (newfd < 0 && errno == EINTR)
		newfd = open(v[*i], O_RDONLY);
	*i += 1;
	//probe(*i, "ffd_init: ");
	//probe(newfd, "ffd_val: ");
	return (err(newfd, "open error"));
}

int	ffd_end(char *v, int heredoc_flag)
{
	int	newfd;
	int	flag;

	errno = 0;
	if (heredoc_flag)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	else
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	newfd = open(v, flag, 0666);
	while (newfd < 0 && errno == EINTR)
		newfd = open(v, flag, 0666);
	return (err(newfd, "open error"));
}
