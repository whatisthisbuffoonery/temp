#include "h_mlx.h"

//m = (dfy - c) / dfx, c = y1

void	swap_wrapper(t_pt *src, t_pt *dst, float *dx, float *dy)
{
	ft_swapf(&src->fx, &src->fy);
	ft_swapf(&dst->fx, &dst->fy);
	*dy = dst->fy - src->fy;//oh this was backwards
	*dx = dst->fx - src->fx;
}

//say [1, 2] and [10, 6], line size 20
//dx == 9, dy == 4
//m = 4 / 9
//for i == 1, ret.fx = 2.0, ret.fy = 2.44
//upper pixel strength: 1 - 0.44 = 0.56 (2 is higher than 3)
//lower pixel strength: 0.44
//point coords: x = 2, y = 2, y = 3
//propose storing as unsigned int
void	buf_edit(t_data *data, float fx, float fy)//feed in upper pixel
{
	unsigned char	value;
	char			*cache;
	int				x;
	int				y;
	int				line;

	x = fx;
	y = fy;
	if (x < 0 || x >= WIDTH || y >= HEIGHT || y < -1)
		return ;
	line = data->line;
	value = 255 * (fy - y);
	cache = &data->buf[(x * data->bypp) + (y * line)];
	if (y >= 0 && y < HEIGHT)
		*(unsigned int *) cache = ((255 - value) << 16) + WHITE;
	y += 1;
	if (y >= 0 && y < HEIGHT)
		*(unsigned int *) (cache + line) = (value << 16) + WHITE;
}

/*
t_pt	pixel_place(t_pt *src, int i, float m, int steep)
{
	t_pt	ret;

	ret.fx = src->fx + i;
	ret.fy = src->fy + (i * m);
	if (steep)
		ft_swapf(&ret->fx, &ret->fy);
	ret.x = (int) ret.fx; //sure
	ret.y = (int) ret.fy; //eh...?
	return (ret);
}
not in use
*/

void	swap_pt(t_pt *src, t_pt *dst, float *dx, float *dy)
{
	t_pt	tmp;

	tmp = *src;
	*src = *dst;
	*dst = tmp;
	*dy = dst->fy - src->fy;//oh this was backwards
	*dx = dst->fx - src->fx;
}

//upper_pixel = {(src->fx + i), (src->fy + (i * m))} //both casted to ints
//lower_pixel = {(src->fx + i), (src->fy + (i * m) + 1)}
void	xiaolin_wu(t_pt src, t_pt dst, t_data *data)
{
	float	m;
	float	dx;
	float	dy;//sac
	int		steep;

	dy = dst.fy - src.fy;
	dx = dst.fx - src.fx;
	steep = (fabsf(dy) > fabsf(dx));
	if (steep)
		swap_wrapper(&src, &dst, &dx, &dy);
	if (dx < 0)
		swap_pt(&src, &dst, &dx, &dy);
	m = 0.0f;
	if (fabsf(dx) > EPSILON)
		m = dy / dx;//gradient after swap
	while (--dx > 1.99f)//(++i < (int) dx)//starts at 1//i.e. 10.99: 9 8 7 6 5 4 3 2.99//1 2 3 4 5 6 7 8 9 10
	{
		src.fx += 1;
		src.fy += m;
		if (steep)
			buf_edit(data, src.fy, src.fx);
		else
			buf_edit(data, src.fx, src.fy);
	}
}
//i.e. from 2.7 to 8.3//dx = 5.6//previous loop: 1 2 3 4 5//this loop: 4.6 3 2.6 1
