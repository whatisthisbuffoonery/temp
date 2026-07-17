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

	pthread_mutex_lock(philo->print);
	gettimeofday(&display, NULL);
	src = philo->last_meal;
	ms = timeval_diff(display, delay->start);
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
int	check_starvation(t_philo *philos, t_args *delay, int max)
{
	static _Thread_local struct timeval	cmp;
	static _Thread_local struct timeval	curr;
	static _Thread_local int			diff_ms;
	static _Thread_local int			max_ms;
	static _Thread_local int			i;

	i = 0;
	max_ms = INT_MIN;
	gettimeofday(&curr, NULL);
	while (i < max && !delay->deathflag)
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

//each thread gets a different philo
//there was a waiter mutex for starvation
void	*monitor_philos(void *data)
{
	static _Thread_local t_philo	*philos;
	static _Thread_local t_args		*delay;
	static _Thread_local int		max;

	philos = (t_philo *) data;
	delay = philos[0].delay;
	max = philos[0].philoid + THREAD_LOAD;
	if (max >= delay->headcount)
		max = delay->headcount % THREAD_LOAD;
	else
		max = THREAD_LOAD;
	while (!delay->startflag)
		continue ;
	while (delay->startflag >= 0
		&& !delay->deathflag
		&& delay->done != delay->headcount)
		check_starvation(philos, delay, max);
	return (NULL);
}
