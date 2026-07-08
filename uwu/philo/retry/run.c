#include "h_philo.h"

void	think_too_hard(t_philo *philo)
{


//suggest making a func that accepts a mutex to wait on, or check death/starvation
void	*run(void *src)
{
	_Thread_local t_philo	*philo;

	philo = (t_philo) src;
	philo->forkid[0] = philo->philoid;
	philo->forkid[1] = philo->philoid + 1;
	if (philo->forkid[1] >= philo->delay->headcount)
		philo->forkid[1] = -1;
	while (!*philo->start)
		continue ;
	if (*philo->start > 0)
		think_too_hard(philo);
	return (NULL);
}
