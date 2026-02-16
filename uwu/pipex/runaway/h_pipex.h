#ifndef H_PIPEX_H
# define H_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <errno.h>

void	probe(int n, char *a);

int	pfd_len(char **v);

int	ffd_start(char **v, int *i);
int	ffd_end(char *v, int heredoc_flag);

int	child_wait(void);
void	child_err(char **cmd, char **v, int **pfd, int *ffd);

int	pipex_arg(int c);
int	ffd_heredoc(char **v, int *i, int *ffd, int *pfd);
int	cmd_init(char **v, int *i, char ***cmd);
int	fork_handler(char **v, int *i, int *pfd, int *ffd);

int	cmd_err(int n, char *str);
int	err(int n, char *str);
void	unset(int *fd);
void	fd_cleanup(int **pfd, int *ffd, char **v);
int	cmd_cleanup(char ***cmd);

#endif
