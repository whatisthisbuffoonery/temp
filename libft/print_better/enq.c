
static void	enq(t_queue **q, t_queue *tmp)
{
	t_queue	*f;
	if (!tmp)//on any bad input
	{
		clear_q(q);
		return ;
	}
	if (!*q)
	{
		*q = tmp;
		return ;
	}
	f = *q;
	while (f->next)
		f = f->next;
	f->next = tmp;
}