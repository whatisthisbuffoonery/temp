#include "h_philo.h"

int	pls_delet_libft;


int	thread_init(t_init_philo *init, t_philo *philos, pthread_t **thread)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	*thread = malloc(sizeof(pthread_t), init->num_of_philos);
	if (!*thread)
		return (1);
	while (i < init->num_of_philos)
	{
		if (pthread_create(&(*thread)[i], NULL, philo, &philos[i]))
		{
			flag = 1;
			break;
		}
		i ++;
	}
	while (flag && i >= 0)
	{
		pthread_join((*thread)[i], NULL);
		i --;
	}
	return (flag);
}

//if time to eat == time to die, they will die immediately
int	main(int c, char **v)
{
	t_init_philo	init;
	pthread_t		*thread;
	t_philo			*philos;

	(void) pls_delet_libft;
	if (args(c, v, &init) || init_mutexes(&init) || philo_init(&init, &philos))
		return (1);
	exit(1);
	//pthread_mutex_lock
	if (thread_init(&init, philos, &thread))
	{
		free(philos);
		return (mutex_cleanup(init, init->num_of_philos));
	}
}
