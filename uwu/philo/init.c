#include "h_philo.h"

int	digit_check(char **v)
{
	int	i;
	int	k;

	k = 1;
	while (v[k])
	{
		i = 0;
		while (v[k][i])
		{
			if (!ft_isdigit(v[k][i]))//reject +-
				return (1);
			i ++;
		}
		k ++;
	}
	return (0);
}

struct timeval	timeval_init(char *v)
{
	int				src;
	struct timeval	ret;

	src = ft_atoi(v);
	ret.tv_sec = src / 1000;
	ret.tv_usec = (src % 1000) * 1000;
	return (ret);
}

//check for neg num ofcos
int	args(int c, char **v, t_init_philo *init)
{
	if (c != 5 && c != 6)
		return (1);
	if (digit_check(v))
		return (1);
	ft_memset(init, 0, sizeof(t_init_philo));
	init->num_of_philos = ft_atoi(v[1]);
	init->die_delay = timeval_init(v[2]);
	init->eat_delay = timeval_init(v[3]);
	init->sleep_delay = timeval_init(v[4]);
	init->eat_limit = 0;//honestly dont need the bool	
	init->eat_limit_set = (v[5] != NULL);
	if (init->eat_limit_set)
		init->eat_limit = ft_atoi(v[5]);
	return (0);
}

int	init_mutexes(t_init_philo *init)
{
	int	i;

	if (pthread_mutex_init(&init->waiter, NULL))
		return (1);
	if (pthread_mutex_init(&init->control, NULL))
	{
		pthread_mutex_destroy(&init->waiter);
		return (1);
	}
	i = 0;
	init->forks = malloc(sizeof(pthread_mutex_t) * init->num_of_philos);
	if (!init->forks)
		return (mutex_cleanup(init, 0));
	while (i < init->num_of_philos)
	{
		if (pthread_mutex_init(&init->forks[i], NULL))
			return (mutex_cleanup(init, i));
		i ++;
	}
	return (0);
}

void	set_index(t_philo *iter, int n, int max)
{
	iter->id = n + 1;
	iter->index[0] = n;
	iter->index[1] = n + 1;
	if (n + 1 > max)
		iter->index[0] = 0;
}

int	philo_init(t_init_philo *init, t_philo **philos)
{
	int			i;
	t_philo		*iter;

	*philos = malloc(sizeof(t_philo) * init->num_of_philos);//double check i didnt 0 index this
	if (!*philos)
		return (mutex_cleanup(init, init->num_of_philos));
	i = 0;
	iter = *philos;
	while (i < init->num_of_philos)
	{
		iter[i].waiter = &init->waiter;
		iter[i].control = &init->control;
		iter[i].forks = init->forks;
		iter[i].start = &init->start;
		iter[i].eat_delay = &init->eat_delay;
		iter[i].sleep_delay = &init->sleep_delay;
		iter[i].die_delay = &init->die_delay;
		iter[i].eat_limit = NULL;
		if (init->eat_limit_set)
			iter[i].eat_limit = &init->eat_limit;
		iter[i].stop = &init->stop;
		set_index(&iter[i], i, init->num_of_philos - 1);
		i ++;
	}
	return (0);
}
