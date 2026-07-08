#include "h_philo.c"

int	timeval_done(t_args *delay, struct timeval curr, struct timeval cmp)
{}

struct timeval	timeval_init(char *v)
{
	struct timeval	ret;
	int				src;

	src = ft_atoi(v);
	ret.tv_sec = src / 1000;
	ret.tv_usec = (src % 1000) * 1000;
	return (ret);
}
