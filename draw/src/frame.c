#include "h_mlx.h"

int stuff = 0;//fu

void	timer(struct timeval start, struct timeval end)
{
	ft_putstr("start:");
	ft_putnbr(start.tv_sec);
	ft_putstr(", ");
	ft_putnbr(start.tv_usec);
	ft_putstr("\nend:");
	ft_putnbr(end.tv_sec);
	ft_putstr(", ");
	ft_putnbr(end.tv_usec);
	ft_putstr("\nresult: ");
	ft_putnbr(end.tv_usec - start.tv_usec);
	ft_putchar('\n');
	stuff ++;
}

int	frame_wait(struct timeval start)
{
	struct timeval	end;
	int				flag;

	gettimeofday(&end, NULL);
	flag = 0;
	if (stuff < 10)//remove me damn you
		timer(start, end);
	if (start.tv_usec + FRAME_MCS >= SECOND_MCS)
		flag = 1;
	while (!flag && end.tv_usec - start.tv_usec < FRAME_MCS)
		gettimeofday(&end, NULL);
	while (flag && start.tv_sec == end.tv_sec)
		gettimeofday(&end, NULL);
	return (0);
}

//#include <stdio.h>

//0.5 on both gets 25%
//1 on one and 0 on the other gets 0
void	goodjoints(t_data *data, t_pt *pt)
{
	float			fx;
	float			fy;
	unsigned char	alpha;
	int				pos;

	fx = pt->fx;
	fy = pt->fy;
//	printf("x: %f, y: %f\n", pt->fx, pt->fy);
	if (fx < 0 || fy < 0 || fx >= WIDTH || fy >= HEIGHT)
		return ;
	alpha = 255 * (fx - (int) fx) * (fy - (int) fy);
	pos = (fx * data->bypp) + (fy * data->line);
//	printf("number: %d\n", pos);
	*(unsigned int *) &data->buf[pos] = (alpha << 16) + WHITE;
	//*(unsigned int *) &data->buf[pos] = 0xFFFFFFFF;
}

void	probe(char *a, int n)
{
	ft_putstr(a);
	ft_putstr(": ");
	ft_putnbr(n);
	ft_putchar('\n');
}

void	debug(t_data *data)
{
	probe("line", data->line);
	probe("bipp", data->bipp);
	probe("max?", (HEIGHT + 1) * data->line);
}

//note i have no idea where to squeeze in drawing the vector point itself
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
//	debug(data);
	y_lim = size-- - line;//yes i bumped it down to 0 index
	while (src < size)
	{
		if (src / line == (src + 1) / line)
			xiaolin_wu(pt[src], pt[src + 1], data);
		if (src < y_lim)
			xiaolin_wu(pt[src], pt[src + line], data);
//		goodjoints(data, &pt[src]);
		src ++;
	}
//	goodjoints(data, &pt[src]);
	//ft_putstr("a\n");
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	//ft_putstr("a\n");
}
//#include <stdio.h>
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
//	printf("angles x: %f, y: %f\n", view->x, view->y);
}


int	draw_frame(void *param)
{
	struct timeval	start;
	t_data	*data;
	t_keys	*keys;

	gettimeofday(&start, NULL);
	
	data = (t_data *) param;
	keys = &data->param.keys;
//	printf("test2: %f\n", data->param.view.scale);
	ft_memset(data->buf, 0, data->line * (HEIGHT + 1));
	change_view(&data->param.view, data->param.keys);//I still remember scale is in there
	if (keys->w != keys->s || keys->a != keys->d || keys->q != keys->e)
		rasterise(data->param.pt, data->param.view, data->size, data);
//	scale(data->pt, &data->view.scale);
//	bresenham(data);
	goodlines(data);//xiaolin wu
	(void) keys;
	//int i = 0;
	//int k;
	// while (i < data->size)
	// {
	// 	k = 0;
	// 	while (k < 100)
	// 	{
	// 		goodjoints(data, &data->param.pt[i]);
	// 		data->param.pt[i].fy += 0.1f;
	// 		k ++;
	// 	}
	// 	data->param.pt[i++].fy -= 10;
	// }
		
	frame_wait(start);
	//ft_putstr("a\n");
	//round float to pixel int coords (math)
	//calculate lines for out of bounds vectors
	//deal with mlx syntax fuckery
	//push img (1 line norminette KO WOOOOOOOOOOOOOO)
	//XIAOLIN WUUUU
	//XUE HUAAAAAA PIAOOO PIAOOOOOOOOOOOOO

	return (0);
}
