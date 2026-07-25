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
	sem_t	*start;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*waiter;
}			t_sembox;

typedef struct s_args;
{
	int

#endif
