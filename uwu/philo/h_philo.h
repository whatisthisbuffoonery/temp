#ifndef H_PHILO_H
# define H_PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define RETRY 2000

//eat_limit will be null for non specified
typedef struct s_philo
{
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*control;
	pthread_mutex_t	*fork_mutex;
	struct timeval	*start;
	struct timeval	*eat_delay;
	struct timeval	*sleep_delay;
	struct timeval	*die_delay;
	struct timeval	current;
	int				index[2];
	int				id;
	int				*eat_limit;
	int				*stop;
	int				*forks;
}					t_philo;

typedef struct s_init_philo
{
	pthread_mutex_t	waiter;
	pthread_mutex_t	control;
	pthread_mutex_t	*forks;
	struct timeval	start;
	struct timeval	eat_delay;
	struct timeval	sleep_delay;
	struct timeval	die_delay;
	struct timeval	current;
	int				eat_limit;
	int				eat_limit_set;
	int				stop;
	int				num_of_philos;
}					t_init_philo;

int	args(int c, char **v, t_init_philo *init);

#endif
