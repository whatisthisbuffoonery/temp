#include "h_philo.h"

void	timeval_find_max(struct timeval *max, struct timeval *test)//new libft func
{
	test->tv_sec = -1;
	test->tv_usec = -1;
	if (test->tv_sec > 0)
		max->tv_sec = -1;
	else
	{
		max->tv_sec = 1;
		max->tv_sec <<= (sizeof(max->tv_sec) * CHAR_BIT) - 1;
		max->tv_sec = ~max->tv_sec;
	}
	if (test->tv_usec > 0)
		max->tv_usec = -1;
	else
	{
		max->tv_usec = 1;
		max->tv_usec <<= (sizeof(max->tv_usec) * CHAR_BIT) - 1;
		max->tv_usec = ~max->tv_usec;
	}
}

int	timeval_diff(struct timeval src1, struct timeval src2)
{
	static _Thread_local struct timeval	curr;
	static _Thread_local struct timeval	test;
	static _Thread_local struct timeval max;
	static _Thread_local int			carry;

	curr.tv_usec = src1.tv_usec - src2.tv_usec;
	carry = (src1.tv_usec < src2.tv_usec);
	curr.tv_sec = (src1.tv_sec - src2.tv_sec) - carry;
	if (!test.tv_sec)
		timeval_find_max(&max, &test);
	if (carry)
		curr.tv_usec += (1000 * 1000) + 1;
	if (src1.tv_sec < src2.tv_sec)
		curr.tv_sec += (max.tv_sec) + (1 - carry);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

int	timeval_diff_atomic(struct timeval src1, _Atomic struct timeval src2)
{
	static _Thread_local struct timeval	input;

	input = src2;
	return (timeval_diff(src1, input));
}

struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg)
{
	static _Thread_local struct timeval	display;
	static _Thread_local struct timeval	src;
	static _Thread_local int			ms;

	gettimeofday(&display, NULL);
	src = philo->last_meal;
	ms = timeval_diff(display, delay->start);
	pthread_mutex_lock(philo->print);
	if (!((msg[0] != 'd' && timeval_diff(display, src) >= delay->starve)
		|| delay->deathflag))
	{
		ft_putnbr(ms);
		ft_putchar(' ');
		ft_putnbr(philo->philoid + 1);
		ft_putchar(' ');
		ft_putstr(msg);
		ft_putchar('\n');
	}
	pthread_mutex_unlock(philo->print);
	return (display);
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
		diff_ms = timeval_diff(curr, cmp);
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
//	int	sleep_ms;

	while (delay->startflag >= 0
	&& !delay->deathflag
	&& !check_done(philos, delay))
	{
//		pthread_mutex_lock(philos[0].waiter);
		check_starvation(philos, delay);
//		pthread_mutex_unlock(philos[0].waiter);
		if (!delay->startflag)
			delay->startflag = 1;
//		if (sleep_ms > 5 || sleep_ms <= 0)
//			sleep_ms = 5;
//		if (sleep_ms < 2)
//			sleep_ms = 2;
//		sleep_ms --;
		//usleep(sleep_ms * 1000);//suggest saving min difference to sleep a different amount, max()
		philo_table(delay);
		usleep(1000);//suggest saving min difference to sleep a different amount, max()
	}
}
