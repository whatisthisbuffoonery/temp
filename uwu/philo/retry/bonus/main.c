#include "h_philo_bonus.h"

//reject negative
int	arg_check(t_args *delay, int c, char **v)
{
	int	i;
	int	k;

	if (c != 5 && c != 6)
		return (1);
	k = 1;
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
	return (0);
}

int	init_delay(t_args *delay, int c, char **v)
{
	if (arg_check(c, v))
		return (1);
	ft_memset(delay, 0, sizeof(t_args));
	delay->headcount = ft_atoi(v[1]);
	delay->starve = ft_atoi(v[2]);
	delay->digest = ft_atoi(v[3]);
	delay->sleep = ft_atoi(v[4]);
	if (v[5])
	{
		delay->diet_set = 1;
		delay->diet = ft_atoi(v[5]);
	}
	return (0);
}

int	init_sem(t_sem_box *dst)
{
	dst->waiter = sem_open("/waiter", O_CREAT, 0777, 0);

int	main(int c, char **v)
{
	//stuff
	//one thread in main staring at sem_die
	//same semaphore indicates init failure
	t_philo		philo;//doesnt contain delay this time//just one
	t_args		delay;
	t_sem_box	box;

	if (init_delay(&delay, c, v) || init_sem(&box))
		return (1);
	philo_init(&philo, &delay, &box);
	philo_cleanup(box);
}

void	run(t_philo *philo, t_args *delay)
{
	//pthread_create after fork, which might fail
}
