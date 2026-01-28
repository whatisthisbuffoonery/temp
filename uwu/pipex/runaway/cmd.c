#include "h_pipex.h"

int	cmd_name(char ***cmd)
{
	int		len;
	char	*ret;

	if (!*cmd)
		return (1);
	len = ft_strlen((*cmd)[0]) + ft_strlen("/usr/sbin");
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (cmd_cleanup(cmd));//pointer remember
	ft_strlcpy(ret, "/usr/bin", -1);
	ft_strlcat(ret, (*cmd)[0], len);
	if (access(ret, X_OK))
	{
		ft_strlcpy(ret, "/usr/sbin", -1);
		ft_strlcat(ret, (*cmd)[0], len);
	}
	free((*cmd)[0]);
	(*cmd)[0] = ret;
	return (0);
}

int	cmd_init(char **v, int *i, char ***cmd, int *ffd)
{
	if (*i == 1)
		ffd = pfd_start(v, i);
	else if (!v[*i + 2])//bleh
		ffd = pfd_end(v, *i, !pipex_cmp(v[1], "here_doc"));
	if (*ffd < 0)
		return (1);
	*cmd = ft_split(v[i], ' ');
	if (cmd_name(cmd))
	{
		if (*ffd > 0)
			close(*ffd);
		*ffd = -1;//whyy is main() running out of space
		return (1);
	}
	return (0);
}
