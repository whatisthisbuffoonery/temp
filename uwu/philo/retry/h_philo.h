#ifndef H_PHILO_H
# define H_PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct
{
	struct timeval	digest;
	struct timeval	sleep;
	struct timeval	starve;
	struct timeval	start;
	int				headcount;
	int				diet;
}					t_args;

typedef struct
{
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	int				forkid[2];
}					t_philo;

//I refuse to put the box in philo directly
typedef struct
{
	pthread_mutex_t	waiter;
	pthread_mutex_t	print;//write function will check death flag and starvation
	pthread_mutex_t	*forks;
}					t_mutex_box;

//mutexes: merge printing and death bulb into one, one for waiter, 
//make dedicated funcs for sleeping and checking for starvation

#endif
