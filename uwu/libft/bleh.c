#include "includes/libft.h"

int	main(int c, char **v)
{
	if (c != 4)
		return (1);
	if (!ft_strncmp(v[1], v[2], ft_atoi(v[3])))
		ft_putstr("no ");
	ft_putstr("diff\n");
//	return ((a()), (b()), 0);
}
