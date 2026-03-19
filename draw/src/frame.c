#include "h_mlx.h"

int	frame_wait(struct timeval start)
{
	struct timeval	end;
	int				flag;

	gettimeofday(&end, NULL);
	flag = 0;
	if (start.tv_usec + FRAME_MCS >= SECOND_MCS)
		flag = 1;
	while (!flag && end.tv_usec - start.tv_usec < FRAME_MCS)
		gettimeofday(&end, NULL);
	while (flag && start.tv_sec == end.tv_sec)
		gettimeofday(&end, NULL);
	return (0);
}

void	goodlines(t_data *data)
{
	int		src;
	int		y_lim;
	int		size;
	int		line;
	t_pt	*pt;

	src = 0;
	pt = data->param.pt;
	line = data->x + 1;
	size = data->size;
	y_lim = size-- - line;
	while (src < size)
	{
		if (src / line == (src + 1) / line)
			xiaolin_wu(pt[src], pt[src + 1], data);
		if (src < y_lim)
			xiaolin_wu(pt[src], pt[src + line], data);
		src ++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	change_view(t_view *view, t_keys keys)
{
	view->x += STEP * (keys.w - keys.s);
	view->y += STEP * (keys.d - keys.a);
	view->z += STEP * (keys.q - keys.e);
	view->x += RAD_MAX * ((view->x < 0) - (view->x > RAD_MAX));
	view->y += RAD_MAX * ((view->y < 0) - (view->y > RAD_MAX));
	view->z += RAD_MAX * ((view->z < 0) - (view->z > RAD_MAX));
	if (keys.w != keys.s)
	{
		view->cosx = cosf(view->x);
		view->sinx = sinf(view->x);
	}
	if (keys.a != keys.d)
	{
		view->cosy = cosf(view->y);
		view->siny = sinf(view->y);
	}
	if (keys.q != keys.e)
	{
		view->cosz = cosf(view->z);
		view->sinz = sinf(view->z);
	}
}


int	draw_frame(void *param)
{
	struct timeval	start;
	t_data	*data;
	t_keys	*keys;

	gettimeofday(&start, NULL);
	
	data = (t_data *) param;
	keys = &data->param.keys;
	ft_memset(data->buf, 0, data->line * (HEIGHT + 1));
	change_view(&data->param.view, data->param.keys);
	data->offset_x += 5 * ((keys->right) - (keys->left));
	data->offset_y += 5 * ((keys->down) - (keys->up));
	rasterise(data->param.pt, data->param.view, data->size, data);
	goodlines(data);

	frame_wait(start);

	return (0);
}
