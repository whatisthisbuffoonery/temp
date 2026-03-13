#include "h_mlx.h"

//m = (dfy - c) / dfx, c = y1

void	swap_wrapper(t_pt *src, float *dx, float *dy)
{
	ft_swap(&src.x, &src.y);
	if (dx && dy)
		ft_swapf(dx, dy);
}

//say [1, 2] and [10, 6], line size 20
//dx == 9, dy == 4
//m = 4 / 9
//for i == 1, ret.fx = 2.0, ret.fy = 2.44
//upper pixel strength: 1 - 0.44 = 0.56 (2 is higher than 3)
//lower pixel strength: 0.44
//point coords: x = 2, y = 2, y = 3
void	buf_edit(char *buf, t_pt pixel, int line, int bypp)//feed in upper pixel
{
	char	value;
	char	*cache;

	if (pixel.x < 0 || pixel.x >= WIDTH)
		return ;
	value = 255 * (pixel.fy - pixel.y);
	cache = &buf[(pixel.x * bypp) + (pixel.y * line)];
	if (pixel.y >= 0 && pixel.y < HEIGHT)
		*(unsigned int *) cache = ((255 - value) << 16) + WHITE;
	pixel.y += 1;
	if (pixel.y >= 0 && pixel.y < HEIGHT)
		*(unsigned int *) (cache + line) = (value << 16) + WHITE;
}

t_pt	pixel_place(t_pt *src, int i, float m, int steep)
{
	t_pt	ret;

	ret.fx = src->fx + (float) i;
	ret.fy = src->fy + ((float) i * m);
	if (steep)
		ft_swapf(&ret->fx, &ret->fy);
	ret.x = (int) ret.fx; //sure
	ret.y = (int) ret.fy; //eh...?
	return (ret);
}

//upper_pixel = {(src->fx + i), (src->fy + (i * m))} //both casted to ints
//lower_pixel = {(src->fx + i), (src->fy + (i * m) + 1)}
void	xiaolin_wu(t_pt *src, t_pt *dst, t_data *data, int steep)
{
	float	m;
	float	dx;
	float	dy;
	int		i;
	int		idx;

	dy = src->fy - dst->fy;
	dx = src->fx - dst->fx;
	steep = (dy > dx);
	if (steep)
		swap_wrapper(src, &dx, &dy);
	m = 1;
	if (dx > EPSILON)
		m = dy / dx;//gradient after swap
	i = 0;
	idx = (int) dx;
	while (++i < idx)//starts at 1
		buf_edit(buf,
			pixel_place(src, i, m, steep),
			data->line,
			data->bypp);
	if (steep)//man my libft needs a fukin swap func now
		swap_wrapper(src, NULL, NULL);
}
