#include "h_philo.h"

void	*philo_table(void *data)
{
	t_args	*delay;

	delay = (t_args *) data;
	while (!delay->startflag)
		continue ;
	while (!delay->deathflag
		&& delay->done != delay->headcount
		&& delay->startflag > 0)
	{
		if ((delay->rule != 2 && delay->table < delay->half)
			|| (delay->rule == 2 && !delay->table))
			continue ;
		delay->rule += 1;
		delay->table = 0;
		if (delay->rule >= 3 - !(delay->headcount % 2))
			delay->rule = 0;
	}
	return (NULL);
}

void	philo_sleep(int duration)
{
	static _Thread_local struct timeval	curr;
	static _Thread_local struct timeval	end;

	if (duration <= 0)
		return ;
	gettimeofday(&curr, NULL);
	end.tv_sec = curr.tv_sec + (duration / 1000);
	end.tv_usec = curr.tv_usec + ((duration % 1000) * 1000);
	if (end.tv_usec > 1000 * 1000)
	{
		end.tv_usec -= 1000 * 1000;
		end.tv_sec += 1;
	}
	if (duration > 20)
	{
		usleep((duration - 20) * 1000);
		gettimeofday(&curr, NULL);
	}
	while (curr.tv_sec != end.tv_sec)
		gettimeofday(&curr, NULL);
	while (curr.tv_usec < end.tv_usec)
		gettimeofday(&curr, NULL);
}

void	philo_dine(t_philo *philo, t_args *delay)
{
	pthread_mutex_lock(&philo->forks[philo->forkid[0]]);//print grabbing fork
	print_philo(philo, delay, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->forkid[1]]);
	print_philo(philo, delay, "has taken a fork");
	philo->last_meal = print_philo(philo, delay, "is eating");
//	pthread_mutex_lock(philo->waiter);
	delay->table += 1;
//	pthread_mutex_unlock(philo->waiter);
	philo_sleep(delay->digest);
	pthread_mutex_unlock(&philo->forks[philo->forkid[0]]);
	print_philo(philo, delay, "has let go of a fork");
	pthread_mutex_unlock(&philo->forks[philo->forkid[1]]);
	print_philo(philo, delay, "has let go of a fork");
//	pthread_mutex_lock(philo->waiter);
	delay->forklist[philo->forkid[0]] = 0;
	delay->forklist[philo->forkid[1]] = 0;
//	pthread_mutex_unlock(philo->waiter);
	print_philo(philo, delay, "is sleeping");
	philo_sleep(delay->sleep);//print sleeping
}

//check starvation
//wtf is hanging the program now
int	call_waiter(t_philo *philo, t_args *delay)
{
	int	granted;

	granted = 0;
	pthread_mutex_lock(philo->waiter);
	if (!delay->deathflag
		&& delay->headcount >= 2
		&& !delay->forklist[philo->forkid[0]]
		&& !delay->forklist[philo->forkid[1]]
		&& delay->table < delay->half
		&& philo->rule == delay->rule)
	{
		delay->forklist[philo->forkid[0]] = 1;
		delay->forklist[philo->forkid[1]] = 1;
		granted = 1;
	}
	pthread_mutex_unlock(philo->waiter);
	return (granted && !delay->deathflag);
}

void	think_too_hard(t_philo *philo, t_args *delay)
{
	static _Thread_local int			i;
	static _Thread_local int			lock;
	static _Thread_local int			was_thinking;
	static _Thread_local struct timeval	curr;

	i = 0;
	was_thinking = 0;
	while (!delay->deathflag && (!delay->diet_set || i < delay->diet))
	{
		gettimeofday(&curr, NULL);
		if (timeval_diff_atomic(curr, philo->last_meal) < delay->starve)
		{
//			pthread_mutex_lock(philo->waiter);//move to waiter
			lock = call_waiter(philo, delay);//print thinking if 0
//			pthread_mutex_unlock(philo->waiter);
		}
		if (!lock && !was_thinking)
			print_philo(philo, delay, "is thinking");
		was_thinking = 1;
		if (!lock)
			continue ;
		philo_dine(philo, delay);
		was_thinking = 0;
	/*	usleep(delay->digest * 1000);//eating msg goes here
		philo_locks(philo, delay, "unlock");
		print_philo(philo, delay, "is sleeping");
		usleep(delay->sleep * 1000);//print sleeping */
		i += (lock && delay->diet_set);
	}
	delay->done += 1;
	philo->done = 1;
	//bruh
//	pthread_mutex_lock(philo->print);
//	ft_printf("exit: %d\n", philo->philoid + 1);
//	pthread_mutex_unlock(philo->print);
}


//suggest making a func that accepts a mutex to wait on, or check death/starvation
//for mutexes, lock > run if no death > unlock
void	*run(void *src)
{
	static _Thread_local t_philo	*philo;
	static _Thread_local t_args		*delay;

	philo = (t_philo *) src;
	delay = philo->delay;
	philo->rule = philo->philoid % 2;
	if (philo->philoid == delay->headcount - 1 && delay->headcount % 2)
		philo->rule = 2;
	philo->forkid[0] = philo->philoid;
	philo->forkid[1] = philo->philoid + 1;
	if (philo->forkid[1] >= delay->headcount)
		philo->forkid[1] = 0;
	while (!delay->startflag)
		continue ;
	if (delay->startflag > 0)
		think_too_hard(philo, philo->delay);
	return (NULL);
}
