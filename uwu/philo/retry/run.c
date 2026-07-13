#include "h_philo.h"

void	philo_locks(t_philo *philo, t_args *delay, char *op)
{
	static _Thread_local int	c;

	c = 0;
	if (op[0] == 'l')
		c = 1;
	delay->forklist[philo->forkid[0]] = c;
	if (philo->forkid[1] < delay->headcount)
		delay->forklist[philo->forkid[1]] = c;
	if (op[0] == 'l')
	{
		pthread_mutex_lock(&philo->forks[philo->forkid[0]]);//print grabbing fork
		print_philo(philo, delay, "has taken a fork");
		pthread_mutex_lock(&philo->forks[philo->forkid[1]]);
		print_philo(philo, delay, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->forkid[0]]);
		print_philo(philo, delay, "has let go of a fork");
		pthread_mutex_unlock(&philo->forks[philo->forkid[1]]);
		print_philo(philo, delay, "has let go of a fork");
	}
	if (c)
		delay->table[philo->philoid] = c;//swap to odd/even rule and try
}

void	philo_table(t_args *delay)
{
	int	i;
	int	rule;

	i = 0;
	rule = 0;
	while (i < delay->headcount)
	{
		if (rule == delay->rule && !delay->table[i])
			return ;
		i ++;
		rule = !rule;
	}
	delay->rule = !delay->rule;
	ft_memset(delay->table, 0, delay->headcount * sizeof(char));
}

//check starvation
int	call_waiter(t_philo *philo, t_args *delay)
{
	struct timeval	curr;

	if (!delay->deathflag)
	{
		if (delay->headcount < 2
			|| delay->forklist[philo->forkid[0]]
			|| delay->forklist[philo->forkid[1]]
			|| delay->table[philo->philoid]
			|| philo->rule != delay->rule)
			return (0);
		philo_locks(philo, delay, "lock");
		if (!delay->deathflag)
		{
//			pthread_mutex_lock(philo->print);// move to caller?
			gettimeofday(&curr, NULL);
			philo->last_meal = curr;
			print_philo(philo, delay, "is eating");
		}
//		pthread_mutex_unlock(philo->print);
		philo_table(delay);
		return (!delay->deathflag);
	}
	return (0);
}

void	think_too_hard(t_philo *philo, t_args *delay)
{
	static _Thread_local int	i;
	static _Thread_local int	lock;
	static _Thread_local int	was_thinking;

	i = 0;
	was_thinking = 0;
	while (!delay->deathflag && (!delay->diet_set || i < delay->diet))
	{
		pthread_mutex_lock(philo->waiter);
		lock = call_waiter(philo, delay);//print thinking if 0
		pthread_mutex_unlock(philo->waiter);
		if (!lock && !was_thinking)
		{
			was_thinking = 1;
			print_philo(philo, delay, "is thinking");
		}
		if (!lock || delay->deathflag)
			continue ;
		was_thinking = 0;
		usleep(delay->digest * 1000);//eating msg goes here
		philo_locks(philo, delay, "unlock");
		print_philo(philo, delay, "is sleeping");
		usleep(delay->sleep * 1000);//print sleeping
		i += (lock && delay->diet_set);
	}
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

	philo = (t_philo *) src;
	philo->rule = philo->philoid % 2;
	philo->forkid[0] = philo->philoid;
	philo->forkid[1] = philo->philoid + 1;
	if (philo->forkid[1] >= philo->delay->headcount)
		philo->forkid[1] = 0;
	while (!philo->delay->startflag)
		continue ;
	if (philo->delay->startflag > 0)
		think_too_hard(philo, philo->delay);
	return (NULL);
}
