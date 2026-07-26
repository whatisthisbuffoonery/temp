#ifndef H_PHILO_BONUS_H
# define H_PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <limits.h>
# include <stdatomic.h>

typedef struct s_sembox
{
	sem_t	*start;//really should just use waiter
	sem_t	*forks;
	sem_t	*print;
	sem_t	*waiter;
	sem_t	*bulb;
}			t_sembox;

typedef struct s_args
{
	struct timeval	start;
	struct s_philo	*philos;
	int				digest;
	int				sleep;
	int				starve;
	_Atomic int		done;
	_Atomic int		deathflag;
	int				half;
	int				headcount;
	int				diet;
	int				diet_set;
	_Atomic int		rule;
}					t_args;

#endif
