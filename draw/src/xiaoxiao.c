#include "h_mlx.h"

void	swap_wrapper(t_pt *src, t_pt *dst, float *dx, float *dy)
{
	ft_swapf(&src->fx, &src->fy);
	ft_swapf(&dst->fx, &dst->fy);
	*dy = dst->fy - src->fy;
	*dx = dst->fx - src->fx;
}

void	buf_edit_uint(t_data *data, float fx, float fy)
{
	int				value;
	unsigned int	*buf;
	int				x;
	int				y;
	int				line;

	x = fx;
	y = fy;
	if (x < 0 || x >= WIDTH || y >= HEIGHT || y < -1)
		return ;
	line = data->line / data->bypp;
	buf = &data->ubuf[x + (y * line)];
	value = 0xFF * (fy - y);
	if (y >= 0 && y < HEIGHT)
	    *buf = (0xFF - value) * SHADE;
	y += 1;
	if (y >= 0 && y < HEIGHT)
	    *(buf + line) = value * SHADE;
}

void	buf_edit_char(t_data *data, float fx, float fy)
{
	int		value;
	char	*buf;
	int		x;
	int		y;
	int		line;

	x = fx;
	y = fy;
	if (x < 0 || x >= WIDTH || y >= HEIGHT || y < -1)
		return ;
	line = data->line;
	buf = &data->buf[(x * data->bypp) + (y * line)];
	value = 0xFF * (fy - y);
	if (data->bipp == 24)
	{
		if (y >= 0 && y < HEIGHT)
			*(unsigned int *) buf = (0xFF - value) * SHADE;
		y += 1;
		if (y >= 0 && y < HEIGHT)
			*(unsigned int *) (buf + line) = value * SHADE;
		return ;
	}
	if (y >= 0 && y < HEIGHT)
		*(unsigned int *) (buf + line) = 0xFF;
}

void	swap_pt(t_pt *src, t_pt *dst, float *dx, float *dy)
{
	t_pt	tmp;

	tmp = *src;
	*src = *dst;
	*dst = tmp;
	*dy = dst->fy - src->fy;
	*dx = dst->fx - src->fx;
}

void	xiaolin_wu(t_pt src, t_pt dst, t_data *data)
{
	float	m;
	float	dx;
	float	dy;
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
		m = dy / dx;
	while (src.fx < dst.fx)
	{
		src.fx += 1;
		src.fy += m;
		if (steep)
			data->buf_edit(data, src.fy, src.fx);
		else
			data->buf_edit(data, src.fx, src.fy);
	}
}
