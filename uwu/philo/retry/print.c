#include "h_philo.h"

int	timeval_diff(struct timeval *src1, struct timeval *src2)
{
	int	a;
	int	b;

	a = (src1->tv_sec * 1000) + (src1->tv_usec / 1000);
	b = (src2->tv_sec * 1000) + (src2->tv_usec / 1000);
	return (a - b);
}

void	print_philo(t_philo *philo, t_args *delay, char *msg)
{
	struct timeval	display;
	struct timeval	src;
	int				ms;

	pthread_mutex_lock(philo->print);
	gettimeofday(&display, NULL);
	src = philo->last_meal;
	if (!((msg[0] != 'd' && timeval_diff(&display, &src) >= delay->starve)
		|| delay->deathflag))
	{
		ms = timeval_diff(&display, &delay->start);
		ft_putnbr(ms);
		ft_putchar(' ');
		ft_putnbr(philo->philoid + 1);
		ft_putchar(' ');
		ft_putstr(msg);
		ft_putchar('\n');
	}
	pthread_mutex_unlock(philo->print);
}

//I will actually make up my mind on cmp funcs after making bad ones fmllll
//move curr back to local
int	check_starvation(t_philo *philos, t_args *delay)
{
	struct timeval	cmp;
	struct timeval	curr;
	int				diff_ms;
	int				max_ms;
	int				i;

	i = 0;
	max_ms = INT_MIN;
	gettimeofday(&curr, NULL);
	while (i < delay->headcount && !delay->deathflag)
	{
		cmp = philos[i].last_meal;
		diff_ms = timeval_diff(&curr, &cmp);
		if (!philos[i].done && diff_ms >= delay->starve)
		{
			print_philo(&philos[i], delay, "died"); //calculate timestamp from last meal + starvation, NOT CURR TIME //VETO
			delay->deathflag = 1;
		}
		else if (max_ms < diff_ms)
			max_ms = diff_ms;
		i ++;
	}
	return (delay->starve - max_ms);
}

int	check_done(t_philo *philos, t_args *delay)
{
	int	i;

	i = 0;
	while (i < delay->headcount)
	{
		if (!philos[i].done)
			return (0);
		i ++;
	}
	return (1);
}

//still use print mutex for eating and this
//philo will never set death flag
void	monitor_philos(t_philo *philos, t_args *delay)
{
	int	sleep_ms;

	while (delay->startflag >= 0
	&& !delay->deathflag
	&& !check_done(philos, delay))
	{
		pthread_mutex_lock(philos[0].waiter);
		sleep_ms = check_starvation(philos, delay);
		pthread_mutex_unlock(philos[0].waiter);
		if (!delay->startflag)
			delay->startflag = 1;
		if (sleep_ms > 5 || sleep_ms <= 0)
			sleep_ms = 5;
		usleep(sleep_ms * 1000);//suggest saving min difference to sleep a different amount, max()
	}
}
