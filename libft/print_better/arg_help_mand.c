#include "header_mand.h"

int	uint_help(char *ret, int flag, int *i)
{
	int	k;

	if (!ret)
		return (1);
	if (flag)
	{
		k = 0;
		while (ret[k] == ' ' && k < *i)
			k ++;
		ret[k] = '0';
		ret[k + 1] = 'x';
		if (arg == 'X')
			ret[k + 1] = 'X';
		*i += flag;//handle_flag placed it after flag requirements, used to be i = flag
	}
	return (0);
}
//the above mostly works, but for bonus we may want to place the 0x earlier
//walk k bytes until either encountering a 0 or catching up to *i

//model: *i = max(width, prec) minus size, min 0
//if flag, follow the above to place prefix and then add 2 to *i regardless what the other circumstances are
//if !flag, do nothing

void	int_help(char *ret, int flag, t_queue *q, int *index)
{
	int	i;
	int	c;
	int	has_sign

	i = 0;
	has_sign = (q->flags && q->flags->plus_space > 0);
	if (flag)
		ret[i++] = -1;
	else if (has_sign)
	{
		c = q->flags->plus_space;
		ret[i++] = c;
	}
	if (i)
		*index += 1;
}
