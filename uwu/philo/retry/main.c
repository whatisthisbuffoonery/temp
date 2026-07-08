#include "h_philo.h"

void	init_delay(t_args *delay, char **v)
{
	delay->headcount = ft_atoi(v[1]);
	delay->starve = timeval_init(v[2]);
	delay->digest = timeval_init(v[3]);
	delay->sleep = timeval_init(v[4]);
	delay->diet = 0;
	if (v[5])
		delay->diet = ft_atoi(v[5]);
}

int	arg_check(t_args *delay, int c, char **v)
{
	int	i;
	int	k;

	if (c != 5 && c != 6)
		return (1);
	ft_memset(delay, 0, sizeof(t_args));
	k = 0;
	while (v[k])
	{
		i = 0;
		while (v[k][i])
		{
			if (v[k][i] < '0' || v[k][i] > '9')
				return (1);
			i ++;
		}
		k ++;
	}
	init_delay(delay, v);
	return (0);
}

void	headcount_cleanup(
		t_philo *philos,
		pthread_t *threads,
		t_args *delay,
		t_mutex_box *mutexes)
{
	int	i;

	i = 0;
	while (philos && threads && i < delay->headcount)
		pthread_join(threads[i++]);
	i = 0;
	while (i < delay->headcount)
		pthread_mutex_destroy(mutexes->forks[i++]);
	pthread_mutex_destroy(mutexes->print);
	pthread_mutex_destroy(mutexes->waiter);
	free(philos);
	free(threads);
	free(mutexes->forks);
}

//delay has like 5 timevals
int	main(int c, char **v)
{
	t_args		delay;
	pthread_t	*threads;
	t_philo		*philos;
	t_mutex_box	mutexes;
	int			start;//can be 1, 0, -1

	threads = NULL;
	philos = NULL;
	start = 0;
	if (arg_check(&delay, c, v)
		|| init_mutexes(&mutexes, &delay))
		return (1);
	start = init_philo(&philos, &threads, &delay, &mutexes);
	headcount_cleanup(philos, threads, &delay, &mutexes);
}
