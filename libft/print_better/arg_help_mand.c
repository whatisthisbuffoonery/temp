#include "header_mand.h"

int	uint_help(char *ret, int flag, int *i)
{
	if (!ret)
		return (1);
	if (flag)
	{
		ret[*i] = '0';
		ret[*i + 1] = 'x';
	}
	*i += flag;//handle_flag placed it after flag requirements, used to be i = flag
	return (0);
}
//the above mostly works, but for bonus we may want to place the 0x earlier
//walk k bytes until either encountering a 0 or catching up to *i

//model: *i = max(width, prec) minus size, min 0
//if flag, follow the above to place prefix and then add 2 to *i regardless what the other circumstances are
//if !flag, do nothing
