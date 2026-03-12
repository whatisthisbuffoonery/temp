#include "h_mlx.h"

int	clicked_x(void *param)
{
	return (fdf_cleanup((t_data *) param, ((t_data *) param)->param.pt));
}

int	esc_key(int keycode, void *param)
{
	if (keycode != XK_Escape)
		return (0);
	return (fdf_cleanup((t_data *) param, ((t_data *) param)->param.pt));
}

int	pressed_key(int keycode, void *param)
{
	t_keys	*keys;

	keys = (t_keys *) param;
	if (keycode == 'q')
		keys->q = 1;
	if (keycode == 'w')
		keys->w = 1;
	if (keycode == 'e')
		keys->e = 1;
	if (keycode == 'a')
		keys->a = 1;
	if (keycode == 's')
		keys->s = 1;
	if (keycode == 'd')
		keys->d = 1;
	return (0);
}

int	released_key(int keycode, void *param)
{
	t_keys	*keys;

	keys = (t_keys *) param;
	if (keycode == 'q')
		keys->q = 0;
	if (keycode == 'w')
		keys->w = 0;
	if (keycode == 'e')
		keys->e = 0;
	if (keycode == 'a')
		keys->a = 0;
	if (keycode == 's')
		keys->s = 0;
	if (keycode == 'd')
		keys->d = 0;
	return (0);
}

//colour: 0x00RRGGBB
int	loop_me(t_data data, t_pt *pt, t_angle angle)//man I want int coords//convert from float vectors to int pixels before breisenham
{//change cleanup to non ptr
	t_param	param;
	t_keys	keys;

	keys = {.q = 0, .w = 0, .e = 0, .a = 0, .s = 0, .d = 0};
	param = {.angle = angle, .pt = pt, .keys = keys};//put scale in angle
	data.param = param;
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, clicked_x, &data);//same func prototype as keypress
	mlx_hook(data.win, KeyPress, KeyPressMask, esc_key, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, pressed_key, &data.param.keys);//calls scale and angle modifiers, then ras and brei
	mlx_key_hook(data.win, released_key, &data.param.keys);//does release key
	mlx_loop_hook(data.mlx, draw_frame, &data);//put sleep in here
	mlx_loop(data.mlx_ptr);
	return (0);
}
