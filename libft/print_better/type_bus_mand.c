#include "header_mand.h"
//id need a third func for this, say, give token() a while help and drag count_flag here
int	type_bus(t_queue *q, const char *format, char *type)
{
	(void) type;//sheit
	if (!q)
		return (0);
	q->arg = format[0];
	return (0);
}
