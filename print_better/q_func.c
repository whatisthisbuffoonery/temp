#include "ft_printf.h"

void	clear_q(t_queue **q, char *ret)
{
	t_queue	*f;
	t_queue *tmp;

	f = NULL;
	if (q && *q)
		f = *q;
	while (f)
	{
		tmp = f->next;
		if (f->str && f->str != ret)//mmmmm
			free(f->str);
		if (f->flags)
			free (f->flags);
		free(f);
		f = tmp;
	}
	if (q)
		*q = NULL;
}

t_queue	*q_new(void)
{
	t_queue	*tmp;

	tmp = malloc(sizeof(t_queue));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->str = NULL;//hm
	tmp->flags = NULL;
	tmp->arg = '\0';
	tmp->type = nil;
	return (tmp);
}

static int	nono(t_queue *new)
{
	write(1, "nono? WHAT DO YOU MEAN NONO\n", 28);
	if (new)
		free(new);
	return (1);
}

int enq(t_queue **q, t_queue *new)
{
	t_queue *f;

	if (!q)
		return (nono(new));//you serious?
	if (!new)
	{  
		clear_q(q, 0);
		return (1);
	}
	if (!*q)
	{
		*q = new;
		return (0);
	}
	f = *q;
	while (f->next)
		f = f->next;
	f->next = new;
	return (0);
}
