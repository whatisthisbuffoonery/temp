/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:18:22 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 16:18:22 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

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

char	*find_path(char **e, char **path)
{
	int		i;
	int		len;
	char	*prefix;

	i = 0;
	prefix = "PATH=";
	len = ft_strlen(prefix);
	while (e[i])
	{
		if (!ft_strncmp(e[i], prefix, len) && ft_strlen(e[i]) > len)
		{
			*path = &e[i][len];
			return (*path);
		}
		i ++;
	}
	return (NULL);
}

int	cmd_init(char **v, int *i, char ***cmd, char **e)
{
	char	**env;
	char	*path;
	int		flag;

	flag = 0;
	path = NULL;
	env = NULL;
	//cmd_name does not fail on null
	if (!ft_strchr(v[*i], '/') && !find_path(e, &path))//set errno to ENOENT, also call strchr here
		return (cmd_err(-1, "command not found"));
	if (path)
	{
		env = ft_split(path, ':');
		if (!env)
			return (err(-1, v[*i]));
	}
	*cmd = ft_split(v[*i], ' ');
	if (!*cmd)
		err(-1, v[*i]);
	if (!*cmd || cmd_name(cmd, env))//null env possible
		flag = 1;//ai cant figure out whether to continue on permission fail fuuuuu
	cmd_cleanup(&env);
	return (flag);
}
