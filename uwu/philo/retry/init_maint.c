#include "h_philo.h"

void	maint_cleanup(t_maint *maint, int size)
{
	int	i;

	if (maint->do_not_cleanup)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_join(maint->threads[i], NULL);
		i ++;
	}
	free(maint->threads);
	maint->do_not_cleanup = 1;
	pthread_join(maint->tabler, NULL);
}

int	init_maint(t_maint *dst, t_args *delay, t_philo *philos)
{
	int	i;
	int	k;

	ft_memset(dst, 0, sizeof(t_maint));
	dst->size = (delay->headcount / 10) + (delay->headcount % 10 != 0);
	if (!malloc_cond((void **) &dst->threads, dst->size * sizeof(pthread_t))
		|| pthread_create(&dst->tabler, NULL, philo_table, delay))
	{
		free(dst->threads);
		dst->do_not_cleanup = 1;
		return (1);
	}
	i = 0;
	while (i < dst->size)
	{
		k = i * 10;
		if (pthread_create(&dst->threads[i], NULL, monitor_philos, &philos[k]))
		{
			maint_cleanup(dst, i);
			return (1);
		}
		i ++;
	}
	return (0);
}
