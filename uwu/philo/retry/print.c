#include "h_philo.h"
/*
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
*/
struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg)
{
	static _Thread_local char			buf[50];
	static _Thread_local struct timeval	display;
	static _Thread_local struct timeval	src;
	static _Thread_local int			ms;
	static _Thread_local int			i;

	gettimeofday(&display, NULL);
	src = philo->last_meal;
	ms = timeval_diff(display, delay->start);
	i = bufnum(buf, ms, 50);
	if (i + 1 < 50)
	{
		buf[i++] = ' ';
		i += bufnum(&buf[i], philo->philoid + 1, 50 - i);
		if (i + 1 < 50)
			buf[i++] = ' ';
	}
	ft_strlcpy(&buf[i], msg, 50 - i);// NEEDS THREAD LOCAL IMPLEMENTATION
	write(1, buf, i + ft_strlen(msg));
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
