int ffd_heredoc(char **v, int *i, int *ffd, int *pfd)
{
    (void) v;
    (void) i;
    (void) ffd;
    (void) pfd;

    return (0);
}

int heredoc_cond(char **v)
{
    (void) v;
    return (0);
}

int pipex_arg(int n)
{
    return ((n != 5));
}