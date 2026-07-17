#include "h_philo.h"

//gettimeofday can't really fail
int	start_timeval(t_args *delay, t_philo *philos)
{
	int	i;

	if (gettimeofday(&delay->start, NULL))
		return (-1);
	i = 0;
	while (i < delay->headcount)
		philos[i++].last_meal = delay->start;
	if (delay->headcount < 1)
		return (-1);
	return (0);//zero
}

//get run func to set its own forkid
int	init_philo(
		t_philo **philos,
		pthread_t **threads,
		t_args *delay,
		t_mutex_box *mutexes)
{
	int	i;

	if (!malloc_cond((void **) threads, delay->headcount * sizeof(pthread_t))
		|| !malloc_cond((void **) philos, delay->headcount * sizeof(t_philo)))
		return (-1);
	i = 0;
	delay->philos = *philos;
	ft_printf("headcount: %d\n", delay->headcount);
	while (i < delay->headcount)
	{
		(*philos)[i].waiter = &mutexes->waiter;
		(*philos)[i].print = &mutexes->print;
		(*philos)[i].forks = mutexes->forks;
		(*philos)[i].delay = delay;
		(*philos)[i].philoid = i;
		if (pthread_create(&(*threads)[i], NULL, run, &(*philos)[i]))
		{
			while (i-- > 0)
				pthread_join((*threads)[i], NULL);
			free(*threads);
			*threads = NULL;
			return (-1);
		}
		i ++;
	}
	return (0);
}
