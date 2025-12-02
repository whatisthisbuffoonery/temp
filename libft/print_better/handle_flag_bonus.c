#include "header_mand.h"
//flag null check maybe done before this

static char	*handle_flag_init(size_t, size, t_queue, *q, int *len)//plan to set some flags to 0
{
	len = size;
	if (len < q->flags->precision)
		len = q->flags->precision;
	if (len < q->flags->width)
		len = q->flags->width;
	len += (q->flags->plus_space > 0);
	ret = malloc(len * sizeof(char));
	return (ret);
}

char	*handle_flag(size_t size, t_queue *q, int *index)//I just have to take out 0x first dont i
{
	char	*ret;
	int		len;
	int		width;
	int		prec;
	int		start;

	ret = handle_flag_init(size, q, &len);
	if (!ret)
		return (NULL);
	width = q->flags->width;
	prec = q->flags->precision;
	if (width > size)//put these in seperate funcs jeez
	{
		if (q->flags->minus_zero != '0')
			ft_memset(ret, ' ', len);
		else if (q->flags->minus_zero == '0')
			ft_memset(ret, '0', len);
	}
	if (prec > size)
	{
		start = (q->flags->plus_space > 0);
		if (!(prec + size >= width || q->flags->minus_zero == '-'))
			start = len - prec;//len already has the extra sign space
		//custom logic per type. wow this sucks
