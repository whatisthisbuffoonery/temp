void	*death_bulb(void *data)
{
	t_args		*delay;
	t_sem_box	*box;

	delay = (t_args *) data;
	box = delay->box;
	while (!delay->startflag)
		continue ;
	if (delay->startflag < 0)
		return (NULL);
	sem_wait(box->death);
	delay->deathflag = 1;
	return (NULL);
}

void	*fork_increment(void *data)
{
	t_args		*delay;
	t_sem_box	*box;

	delay = (t_args *) data;
	box = delay->box;
	while (!delay->startflag)
		continue ;
	if (delay->startflag < 0)
		return (NULL);
	while (!delay->deathflag)
	{
		sem_wait(box->fork_released);
		delay->forks += 1;
	}
	return (NULL);
}

void	*fork_decrement(void *data)
{
	t_args		*delay;
	t_sem_box	*box;

	delay = (t_args *) data;
	box = delay->box;
	while (!delay->startflag)
		continue ;
	if (delay->startflag < 0)
		return (NULL);
	while (!delay->deathflag)
	{
		sem_wait(box->fork_taken);
		delay->forks += 1;
	}
	return (NULL);
}

int	check_starvation(t_philo *philo, t_args *delay, t_sem_box *box)
{
	static _Thread_local struct timeval	cmp;
	static _Thread_local struct timeval	curr;
	static _Thread_local int			diff_ms;

	gettimeofday(&curr, NULL);
	cmp = philos[i].last_meal;
	diff_ms = timeval_diff(curr, cmp);
	if (!philos[i].done && diff_ms >= delay->starve)
	{
		sem_wait(box->waiter);
		print_philo(&philos[i], delay, "died");
		sem_post(box->waiter);
	}
	return (delay->starve - diff_ms);
}

void	*monitor_philos(void *data)
{
	static _Thread_local t_philo	*philo;
	static _Thread_local t_args		*delay;
	static _Thread_local t_sem_box	*box;
	static _Thread_local int		diff;

	philo = (t_philo *) data;
	delay = philo->delay;
	box = delay->box;
	while (!delay->startflag)
		continue ;
	if (delay->startflag < 0)
		return (NULL);
	while (!delay->deathflag && !philo->done)
	{
		diff = check_starvation(philos, delay, box);
		if (diff > SLEEP_THRESHOLD)
			usleep((diff - SLEEP_THRESHOLD) * 1000);
	}
	return (NULL);
}
//check starvation
//two more threads to increment or decrement //two more semaphores too //fml
