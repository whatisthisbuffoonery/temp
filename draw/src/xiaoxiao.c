#include "h_mlx.h"

//m = (dfy - c) / dfx, c = y1
void	xiaolin_wu(t_pt *src, t_pt *dst, int line, int height)
{
	float	m;
	float	dx;
	float	dy;
	int		i;
	int		steep;

	dy = src->fy - dst->fy;
	dx = src->fx - dst->fx;
	steep = (dy > dx);
	if (steep)
	{
		m = dy;
		dy = dx;
		dx = m;
	}
	m = 1;
	if (dx > EPSILON)
		m = dy / dx;
	i = 1;
	while (i < (int) dx)
	{
		upper_pixel = {(src->fx + i), (src->fy + (i * m))} //both casted to ints
		lower_pixel = {(src->fx + i), (src->fy + (i * m) + 1)}
		y_coord = m * (src->fx + i);//
	}
	//...
	if (steep)//man my libft needs a fukin swap func now
}
