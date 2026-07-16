#ifndef H_PHILO_H
# define H_PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdatomic.h>

# include "libft.h" //pls pls remove

typedef struct s_args
{
	struct timeval	start;		//should it?
	struct s_philo	*philos;
	_Atomic char	*table;		//use a counter instead
	_Atomic char	*forklist;
	int	digest;		//should be ms
	int	sleep;		//should be ms
	int	starve;		//should be ms
	_Atomic int		startflag;
	_Atomic int		deathflag;
	int				headcount;
	int				diet;
	int				diet_set;
	_Atomic int		rule;
}					t_args;

typedef struct s_philo
{
	struct timeval		last_meal;
	pthread_mutex_t			*waiter;
	pthread_mutex_t			*print;
	pthread_mutex_t			*forks;
	t_args					*delay;
	int						forkid[2];
	int						philoid;//stored 0 indexed
	int						rule;
	_Atomic int				done;
}							t_philo;

//I refuse to put the box in philo directly
typedef struct s_mutex_box
{
	pthread_mutex_t	waiter;
	pthread_mutex_t	print;//write function will check death flag and starvation
	pthread_mutex_t	*forks;
}					t_mutex_box;


void	*run(void *src);
int	init_philo(
		t_philo **philos,
		pthread_t **threads,
		t_args *delay,
		t_mutex_box *mutexes);
int	init_mutexes(t_mutex_box *dst, t_args *delay);
struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg);
void	monitor_philos(t_philo *philos, t_args *delay);
int	timeval_diff(struct timeval src1, struct timeval src2);
int	timeval_diff_atomic(struct timeval src1, _Atomic struct timeval src2);
void	philo_table(t_args *delay);


//mutexes: merge printing and death bulb into one, one for waiter, 
//make dedicated funcs for sleeping and checking for starvation

#endif
