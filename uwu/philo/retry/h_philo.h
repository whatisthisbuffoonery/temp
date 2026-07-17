#ifndef H_PHILO_H
# define H_PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdatomic.h>

# include "libft.h" //pls pls remove

# define THREAD_LOAD 1

typedef struct s_args
{
	struct timeval	start;		//should it?
	struct s_philo	*philos;
	_Atomic char	*forklist;
	int	digest;		//should be ms
	int	sleep;		//should be ms
	int	starve;		//should be ms
	_Atomic int		table;		//use a counter instead
	_Atomic int		done;		//note this is a counter now
	_Atomic int		startflag;
	_Atomic int		deathflag;
	int				half;
	int				headcount;
	int				diet;
	int				diet_set;
	_Atomic int		rule;
}					t_args;

typedef struct s_philo
{
	struct timeval			last_meal;
	pthread_mutex_t			*waiter;
	pthread_mutex_t			*print;
	pthread_mutex_t			*forks;
	t_args					*delay;
	int						forkid[2];
	int						philoid;//stored 0 indexed
	int						rule;
	_Atomic int				done;
}							t_philo;

typedef struct s_maint
{
	pthread_t	*threads;
	pthread_t	tabler;
	int			size;
	int			do_not_cleanup;
}				t_maint;

//I refuse to put the box in philo directly
typedef struct s_mutex_box
{
	pthread_mutex_t	waiter;
	pthread_mutex_t	print;//write function will check death flag and starvation
	pthread_mutex_t	*forks;
}					t_mutex_box;


int				init_philo(
		t_philo **philos,
		pthread_t **threads,
		t_args *delay,
		t_mutex_box *mutexes);

int				init_mutexes(t_mutex_box *dst, t_args *delay);
struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg);
int				start_timeval(t_args *delay, t_philo *philos);

void			*run(void *src);
void			*monitor_philos(void *data);
void			*philo_table(void *data);

int				init_maint(t_maint *dst, t_args *delay, t_philo *philos);
void			maint_cleanup(t_maint *maint, int size);

int				timeval_diff(struct timeval src1, struct timeval src2);
int				timeval_diff_atomic(struct timeval src1, _Atomic struct timeval src2);

//mutexes: merge printing and death bulb into one, one for waiter, 
//make dedicated funcs for sleeping and checking for starvation

#endif
