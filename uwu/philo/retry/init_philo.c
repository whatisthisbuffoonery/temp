#include "h_philo.h"

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
	while (i < delay->headcount)
	{
		//configure philos first ofc
		if (pthread_create(&(*threads)[i], NULL, run, (*philos)[i]))
		{
			//cleanup
			return (-1);
		}
		i ++;
	}
	return (1);
}
