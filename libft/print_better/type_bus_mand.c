#include "header_mand.h"
//id need a third func for this, say, give token() a while help and drag count_flag here
int	type_bus(t_queue **q, const char *format, char *type)
{
	t_queue	*f;

	(void) type;//sheit
	f = *q;
	if (!f)
		return (0);
	f->arg = format[0];
	return (1);
}
