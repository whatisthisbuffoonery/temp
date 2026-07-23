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
