#include "h_pipex.h"

/*

*/
//		|| !ft_strpart(cmd, "./"))//take out for pipex
int	cmd_cmp(char *cmd)
{
	if (!ft_strncmp(cmd, "/usr/bin/", ft_strlen("/usr/bin/")))
		return (0);
	if (!ft_strncmp(cmd, "/usr/sbin/", ft_strlen("/usr/sbin/")))
		return (0);
	if (!ft_strncmp(cmd, "/bin/", ft_strlen("/bin/")))
		return (0);
	if (!ft_strncmp(cmd, "/sbin/", ft_strlen("/sbin/")))
		return (0);
	return (1);
}

//err.c wooooo
//errno lost on call
//use a diff func for cmd error to skip the initial pipex indicator
int	cmd_name_help(char ***cmd, char *ret, int len)
{
	int	result;

	errno = 0;
	if (!cmd_cmp((*cmd)[0]))
	{
		ft_strlcpy(ret, (*cmd)[0], -1);
		return (cmd_err(access(ret, X_OK), ret));
	}
	ft_strlcpy(ret, "/usr/bin/", -1);
	ft_strlcat(ret, (*cmd)[0], len);
	result = access(ret, X_OK);
	if (!result || errno != ENOENT)
		return (cmd_err(result, (*cmd)[0]));
	errno = 0;
	ft_strlcpy(ret, "/usr/sbin/", -1);
	ft_strlcat(ret, (*cmd)[0], len);
	return (cmd_err(access(ret, X_OK), (*cmd)[0]));
}

int	cmd_name(char ***cmd)
{
	int		len;
	char	*ret;

	len = ft_strlen((*cmd)[0]) + ft_strlen("/usr/sbin/") + 1;
	ret = malloc(len * sizeof(char));
	if (!ret)
	{
		err(-1, (*cmd)[0]);
		return (cmd_cleanup(cmd));
	}
	if (cmd_name_help(cmd, ret, len))
	{
		free(ret);
		return (cmd_cleanup(cmd));
	}
	free((*cmd)[0]);
	(*cmd)[0] = ret;
	return (0);
}

int	cmd_init(char **v, int *i, char ***cmd)
{
	//probe(*i, "index: ");
	*cmd = ft_split(v[*i], ' ');
	if (!*cmd)
		return (err(-1, v[*i]));
	if (cmd_name(cmd))
		return (1);
	*i += 1;
	return (0);
}
