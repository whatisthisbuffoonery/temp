#include "h_mlx.h"

int	frame_wait(void)
{
	struct timeval	start;//need to standardise this to fixed points
	struct timeval	end;
	int				flag;

	gettimeofday(&start, NULL);
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

void	goodlines(t_data *data, int index)
{
	if (index < data->x)
	{
		xiaolin_wu(&data->pt[index], &data->pt[index + 1], data->line);
		goodlines(data, index + 1);
	}
	if (index / data->line < data->y)
	{
		xiaolin_wu(&data->pt[index],
			&data->pt[index + data->x + 1],
			data->line);
		goodlines(data, index + data->x + 1);
	}
}

int	draw_frame(void *param)
{
	t_data	data;
	int		i;

	i = 0;
	data = *(t_data *) param;
	change_view(&data.angle, data.keys);//I still remember scale is in there
	while (i < data.frame)
		rasterise(&data.pt[i++], data.angle, data.angle.scale);
//	bresenham(data);
	goodlines(&data, 0);//xiolin wu
	//round float to pixel int coords (math)
	//calculate lines for out of bounds vectors
	//deal with mlx syntax fuckery
	//push img (1 line norminette KO WOOOOOOOOOOOOOO)
	//XIAOLIN WUUUU
	//XUE HUAAAAAA PIAOOO PIAOOOOOOOOOOOOO

	return (0);
}
