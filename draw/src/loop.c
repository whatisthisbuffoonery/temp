#include "h_mlx.h"

int	clicked_x(void *param)
{
	return (fdf_cleanup((t_data *) param, ((t_data *) param)->param.pt));
}

/*
int	esc_key(int keycode, void *param)
{
	write(1, "\n", 1);
	ft_putnbr(keycode);
	write(1, "\n", 1);
//	if (keycode != 65307)//XK_Escape)
//		return (0);
	return (fdf_cleanup((t_data *) param, ((t_data *) param)->param.pt));
}
*/

int	pressed_key(int keycode, void *param)
{
	t_keys	*keys;

	if (keycode == XK_Escape)
		return (fdf_cleanup((t_data *) param, ((t_data *) param)->param.pt));
	keys = &((t_data *) param)->param.keys;
	if (keycode == 'w')
		keys->w = 1;
	else if (keycode == 'a')
		keys->a = 1;
	else if (keycode == 's')
		keys->s = 1;
	else if (keycode == 'd')
		keys->d = 1;
	else if (keycode == 'q')
		keys->q = 1;
	else if (keycode == 'e')
		keys->e = 1;
	ft_putchar(keycode);
	ft_putchar('p');
	ft_putchar('\n');
	return (0);
}

int	released_key(int keycode, void *param)
{
	t_keys	*keys;

	keys = (t_keys *) param;
	if (keycode == 'w')
		keys->w = 0;
	else if (keycode == 'a')
		keys->a = 0;
	else if (keycode == 's')
		keys->s = 0;
	else if (keycode == 'd')
		keys->d = 0;
	else if (keycode == 'q')
		keys->q = 0;
	else if (keycode == 'e')
		keys->e = 0;
	ft_putchar(keycode);
	ft_putchar('r');
	ft_putchar('\n');
	return (0);
}
//#include <stdio.h>
int	mouse_wheel(int keycode, int x, int y, void *param)
{
	t_data	*data;

	(void) x;
	(void) y;
//	ft_putstr("\nhere\n");
	data = (t_data *) param;
//	printf("test3: %f\n", data->param.view.scale);
	if (keycode == DOWN && data->param.view.scale > 6)
		data->param.view.scale -= 5;
	else if (keycode == UP)
		data->param.view.scale += 5;
	return (0);
}


int	oops(void *param)
{
	struct timeval	start;
	t_data			*data;

	gettimeofday(&start, NULL);
	data = (t_data *) param;
	change_view(&data->param.view, data->param.keys);//I still remember scale is in there
	rasterise(data->param.pt, data->param.view, data->size);
	int i = 0;
	while (i < data->size)
	{
		//printf("\nx: %f, y: %f\n", data->param.pt[i].fx, data->param.pt[i].fy);
		i ++;
	}
	frame_wait(start);
	return (0);
}

//diff file
//colour: 0x00RRGGBB
int	loop_me(t_data data)//man I want int coords//convert from float vectors to int pixels before breisenham
{
	data.param.keys = (t_keys){.w = 0, .a = 0, .s = 0, .d = 0};//, .q = 0, .e = 0};

	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, clicked_x, &data);//works

	mlx_hook(data.win, KeyPress, KeyPressMask, pressed_key, &data);//calls scale and angle modifiers, then ras and brei

//	mlx_hook(data.win, ButtonPress, Button2MotionMask, mouse_wheel, &data);//calls scale and angle modifiers, then ras and brei

	mlx_hook(data.win, KeyRelease, KeyReleaseMask, released_key, &data.param.keys);
	//mlx_key_hook(data.win, released_key, &data.param.keys);//does release key

	mlx_mouse_hook(data.win, mouse_wheel, &data);
//	printf("test1: %f\n", data.param.view.scale);

	mlx_loop_hook(data.mlx, draw_frame, &data);//put sleep in here//keys edit TBA
//	mlx_loop_hook(data.mlx, oops, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
//	fdf_cleanup(&data, data.param.pt);
//	return (0);
	mlx_loop(data.mlx);
//	printf("size: %d\n", data.size);
//	struct timeval start;
//	gettimeofday(&start, NULL);
//	frame_wait(start);
	return (0);
//	mlx_terminate(data.mlx);
}
