
//i == 1 condition to change, rest is ok
//oh my fu I need a new strncmp //then: new read for partial reads and not count \n for limiter
//new loop for partial reads
//!!pipex uses > TRUNC without heredoc and >> no TRUNC with heredoc

int	heredoc_write(int fd, char *line, int len)
{
	int	written;
	int	i;

	if (!line)
		return (1);
	written = 0;
	while (written < len)
	{
		i = write(fd, line + written, len - written);
		if (i < 0)
		{
			close(fd);
			free(line);
			return (1);
		}
		written += i;
	}
	free(line);
	return (0);
}

int	ffd_heredoc(char **v, int *i, int len)//not considering tokens (not told to accept ">>"), export heredoc flag from fork call
{
	int		newfd;
	char	*line;

	newfd = open("tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (newfd < 0)
		return (-1);
	unlink("tmp/here_doc");
	line = gnl(0);
	while (line && pipex_cmp(line, v[2], len))
	{
		if (heredoc_write(newfd, line, len))
			return (-1);
	}
	*i += 2;
	return (newfd);
}

int	ffd_start(char **v, int *i)
{
	int	newfd;

	if (!strcmp(v[1], "here_doc"))
		return (ffd_heredoc(v, i, ft_strlen(v[2])));
	newfd = open(v[1], O_RDONLY);
	return (newfd);
}

int	pfd_end(char **v, int *index, heredoc_flag)
{
	int	i;
	int	newfd;

	i = *index;
	while (v[i + 1])
		i ++;
	if (heredoc_flag)
		newfd = open(v[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		newfd = open(v[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (newfd);
}

int pipex_cmp(char *line, char *v, int v_len)//a one off for a func where heredoc would use a different version
{
	int		line_len;
	int		i;
	char	*tmp;

	line_len = ft_strlen(line);
	if (!v[0] && line[0] == '\n' || line[v_len] != '\n')
		return (0);
	if (line_len > v_len + 1)
		return (1);
	return (strncmp(line, v, v_len));
}
