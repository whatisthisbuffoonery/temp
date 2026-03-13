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

void	goodlines2(t_data *data)
{
	int	x;
	int	y;
	int	src;
	int	line;

	y = 0;
	line = 0;
	while (y <= data->y)
	{
		x = 0;
		while (x < data->x)// 0 index minus 1
		{
			src = line + x;
			xiaolin_wu(&pt[src], &pt[src + 1], data);
			if (y < data->y)
				xiaolin_wu(&pt[src], &pt[src + data->x + 1], data, 0);
			x ++;
		}
		y ++;
		line += data->x;
	}
}

int	draw_frame(void *param)
{
	struct timeval	start;
	t_data	data;
	int		i;

	gettimeofday(&start, NULL);
	i = 0;
	data = *(t_data *) param;
	change_view(&data.angle, data.keys);//I still remember scale is in there
	while (i < data.frame)
		rasterise(&data.pt[i++], data.angle, data.angle.scale);
//	bresenham(data);
	goodlines(&data, 0);//xiolin wu
	frame_wait(start);
	//round float to pixel int coords (math)
	//calculate lines for out of bounds vectors
	//deal with mlx syntax fuckery
	//push img (1 line norminette KO WOOOOOOOOOOOOOO)
	//XIAOLIN WUUUU
	//XUE HUAAAAAA PIAOOO PIAOOOOOOOOOOOOO

	return (0);
}
