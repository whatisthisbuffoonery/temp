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

int	bomb_out(t_args *delay, t_sem_box *box, pid_t *arr, int count)
{
	sem_lightbulb(box->death, delay->heacount);
	sem_lightbulb(box->start, delay->headcount);//this neccesitates a separate sem
	child_wait(arr, count);//frees arr
	unlink_all();
	sem_close(box->waiter);
	sem_close(box->print);
	sem_close(box->forks);
	sem_close(box->death);//doesnt this happen in main
	sem_close(box->start);
	return (0);
	//destroy sems
}

//pid array bruh
//how tf do we agree on start timestamp
int	init_forks(t_philo *philo, t_args *delay, t_sem_box *box, pid_t **arr)
{
	int	i;
	int	pid;

	if (!malloc_cond((void **) arr, delay->headcount * sizeof(pid_t)))
		return (bomb_out(delay, box, *arr, 0));
	i = 0;
	gettimeofday(&delay->start);
	while (i < delay->headcount)
	{
		pid = fork();
		if (pid < 0)
			return (bomb_out(delay, box, *arr, i));//figure out main() cleanup
		else if (!pid)
		{
			philo->philoid = i;
			free(*arr);
			init_philo(philo, delay, box);//diff name la
			exit(0);//...?
		}
		else
			(*arr)[i] = pid;
		i ++;
	}
	sem_lightbulb(box->start, delay->headcount);
	return (0);
}

int	main(int c, char **v)
{
	//stuff
	//one thread in main staring at sem_die
	//same semaphore indicates init failure
	t_philo		philo;//doesnt contain delay this time//just one
	t_args		delay;
	t_sem_box	box;
	pid_t		*arr;

	if (init_delay(&delay, c, v) || init_sem(&box))
		return (1);
	init_forks(&philo, &delay, &box, &arr);
	philo_cleanup(box);
}
