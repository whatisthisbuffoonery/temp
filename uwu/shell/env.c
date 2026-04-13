#include "h_minishell.h"

static void	window_shopping(t_shnode *curr, t_shnode *a, t_shnode *b)
{
	t_shnode	*iter;

	while (a && b)
	{
		if (ft_strcmp(a, b) < 0)
		{
			curr->next = a;
			a = a->next;
		}
		else
		{
			curr->next = b;
			b = b->next;
		}
		curr = curr->next;
	}
	iter = b;
	if (!b)
		iter = a;
	while (iter)
	{
		curr->next = iter;
		curr = curr->next;
		iter = iter->next;
	}
}

static void	merge_split(t_shnode **head, t_shnode **a, t_shnode **b)
{
	t_shnode	*i;
	t_shnode	*k;

	i = *head;
	k = NULL;
	*a = i;
	if (i)
		k = i->next;
	while (k && k->next)
	{
		i = i->next;
		k = k->next->next;
	}
	if (i)
		*b = i->next;
	if (*b)
		i->next = NULL;
}

static void	merge_sort(t_shnode **head)
{
	t_shnode	*a;
	t_shnode	*b;

	a = NULL;
	b = NULL;
	merge_split(head, &a, &b);
	if (a && a->next)
		merge_sort(&a);
	if (b && b->next)
		merge_sort(&b);
	if (b && ft_strcmp(a, b) > 0)
	{
		*head = b;
		b = b->next;
	}
	else
	{
		*head = a;
		a = a->next;
	}
	window_shopping(*head, a, b);
}

/*merge sort section-------------------------------------------------------------------------------*/

int	env_add(t_env *env, t_shnode *src, char *dst)
{
	t_shnode	*ret;
	t_shnode	*iter;
	t_shnode	**list;

	ret = src;
	list = &env->export;
	if (dst[1] == 'n')
	{
		ret = malloc(sizeof(t_shnode));
		if (!ret)
			return (err(-1, "env dup malloc"));
		ret->name = src->name;
		ret->str = src->str;
		list = &env->env;
	}
	if (ret)
		ret->next = NULL;
	iter = *list;
	while (iter && iter->next)
		iter = iter->next;
	if (!iter)
		*list = ret;
	else
		iter->next = ret;
	return (0);
}

t_shnode	*env_init_node(char *e)
{
	t_shnode	*ret;
	int			i;

	ret = malloc(sizeof(t_shnode));
	if (!ret)
		return (NULL);
	i = 0;
	while (e[i] && e[i] != '=')
		i ++;
	ret->name = ft_strndup(e, i);
	if (ret->name)
		ret->str = ft_strdup(&e[i + (e[i] != '\0')]);
	if (!ret->name || !ret->str)
	{
		free(ret->name);
		free(ret);
		return (NULL);
	}
	ret->next = NULL;
	return (ret);
}

int	update_shell_lvl(t_env *dst)
{
	t_shnode	*iter;
	char		*ret;

	iter = find_env("SHLVL", dst->export, ft_strlen("SHLVL"));
	if (!iter)
	{
		iter = env_init_node("SHLVL=1");
		if (!iter)
			return (-1, "could not replace missing shlvl")
		env_add(iter, dst, "env");
		env_add(dst, iter, "export");
		return ;
	}
	if (iter->str)
		ret = ft_itoa(ft_atoi(iter->str) + 1);
	else
		ret = ft_itoa(1);
	if (!ret)
		return (err(-1, "shlvl update error"));
	free(iter->str);
	iter->str = ret;
	iter = find_env("SHLVL", dst->env, ft_strlen("SHLVL"));
	if (!shell_assert(!iter, "shlvl missing in env"))
		iter->str = ret;
	return (0);
}

//technically you would getcwd() here to list the binary name and location
int	update_shell_name(t_env *dst)
{
	t_shnode	*iter;
	char		*ret;

	iter = find_env("SHELL", dst->export, ft_strlen("SHELL"));
	if (!iter)
	{
		iter = env_init_node("SHELL=minishell");
		if (!iter)
			return (-1, "could not replace missing shell name")
		env_add(iter, dst, "env");
		env_add(dst, iter, "export");
		return ;
	}
	ret = ft_strdup("minishell");
	if (!ret)
		return (err(-1, "shell name update error"));
	free(iter->str);
	iter->str = ret;
	iter = find_env("SHELL", dst->env, ft_strlen("SHELL"));
	if (!shell_assert(!iter, "shell name missing in env"))
		iter->str = ret;
	return (0);
}
//init shell level, only init cd dash if null/not present
//also also change SHELL to be minishell, update SHLVL
//dealing with LINES and COLUMNS for display stuff is way outside subject scope
void	env_init(t_env *dst, char **e)
{
	int			i;
	int			k;
	t_shnode	*iter;

	i = 0;
	ft_memset(dst, 0, sizeof(t_env));
	while (e[i])
	{
		iter = env_node_init(e[i]);
		if (err((-!iter), "export node malloc"))
			break ;
		env_add(dst, iter, "env");
		env_add(dst, iter, "export");
		i ++;
	}
	merge_sort(&dst->env);
	update_shell_lvl(dst);
	update_shell_name(dst);
	env_init_cont(dst);
}
