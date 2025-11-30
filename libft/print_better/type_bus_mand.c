#include "header_mand.h"

int	type_bus(t_queue **q, char **dst, const char *format)
{
	t_queue	*f;

	f = *q;
	*dst = NULL;
	if (!f)
		return (0);
	*dst = malloc(2 * sizeof(char)); //practice flags in strings
	if (!*dst)
		return (0); //let caller clean up
	(*dst)[0] = format[0];
	(*dst)[1] = '\0';
	return (1);
}
