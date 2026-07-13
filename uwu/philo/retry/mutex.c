#include "h_philo.h"

//mutex init always returns 0
int	init_mutexes(t_mutex_box *dst, t_args *delay)
{
	int	i;
	int	size;

	size = delay->headcount;
	ft_memset(dst, 0, sizeof(t_mutex_box));
	if (!malloc_cond((void **) &dst->forks, size * sizeof(pthread_mutex_t)))
		return (1);
	i = 0;
	while (i < size)
		pthread_mutex_init(&dst->forks[i++], NULL);
	pthread_mutex_init(&dst->print, NULL);
	pthread_mutex_init(&dst->waiter, NULL);
	return (0);
}
