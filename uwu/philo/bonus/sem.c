#include "h_philo_bonus.h"

void	unlink(void)
{
	sem_unlink(WAITER);
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	sem_unlink(DEATH);
}

void	close_sem(t_sem_box *box)
{
	if (dst->waiter != SEM_FAILED)
		close(dst->waiter);
	if (dst->forks != SEM_FAILED)
		close(dst->forks);
	if (dst->print != SEM_FAILED)
		close(dst->print);
	if (dst->death != SEM_FAILED)
		close(dst->death);
}

int	init_sem(t_sem_box *dst, t_args *delay)
{
	unlink_all();
	dst->waiter = sem_open(WAITER, O_CREAT, 0777, 0);
	dst->forks = sem_open(FORKS, O_CREAT, 0777, delay->headcount);
	dst->print = sem_open(PRINT, O_CREAT, 0777, 0);
	dst->death = sem_open(DEATH, O_CREAT, 0777, 0);
	if (dst->waiter == SEM_FAILED
		|| dst->forks == SEM_FAILED
		|| dst->print == SEM_FAILED
		|| dst->death == SEM_FAILED)
	{
		unlink_all();
		close_sem(dst);
		return (1);
	}
	return (0);
}
