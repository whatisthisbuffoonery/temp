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

# define WAITER "/waiter"
# define PRINT "/print"
# define FORKS "/forks"
# define DEATH "/death"

typedef struct s_sembox
{
	sem_t	*forks;//global
	sem_t	*print;//global
	sem_t	*waiter;//global
	sem_t	*death;
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
}					t_args;

#endif
