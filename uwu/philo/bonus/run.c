#include "h_philo_bonus.h"

//memset delay
int	philo_thread_init(pthread_t *dst, t_args *delay)
{
	if (pthread_create(&dst[0], NULL, philo_death, delay))
		return (1);
	else if (pthread_create(&dst[1], NULL, other_death, delay))
	{
		// set death
		pthread_join(dst[0], NULL);
		return (1);
	}
	return (0);
}

void	think_too_hard(t_philo *philo, t_args *delay, t_sem_box *box)
{
	int	was_thinking;
	int	lock;
	int	forks;
	int	i;

	was_thinking = 0;
	i = 0;
	forks = delay->headcount;
	while (!delay->deathflag && !delay->done
			&& (!delay->diet_set || i < delay->diet))
	{
		lock = call_waiter(delay, box, &forks);//rely on death thread for checking
		if (!lock && !was_thinking)
			print_philo(philo, delay, "is thinking");
		was_thinking = 1;
		if (!lock)
			continue ;
		was_thinking = 0;
		philo_dine(philo, delay, box);
		i ++;
	}
}

void	run(t_philo *philo, t_args *delay, t_sem_box *box)
{
	pthread_t	threads[2];
	//pthread_create after fork, which might fail
	if (philo_thread_init(threads, delay))
		return ;
	sem_wait(box->start);
	think_too_hard(philo, delay, box);
	pthread_join(dst[0], NULL);
	pthread_join(dst[1], NULL);
}
