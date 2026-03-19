#include "h_mlx.h"

int	clicked_x(void *param)
{
	return (fdf_cleanup((t_data *) param, ((t_data *) param)->param.pt));
}

int	keys_cont(int keycode, t_keys *keys, int input)
{
	if (keycode == XK_Left)
		keys->left = input;
	if (keycode == XK_Right)
		keys->right = input;
	if (keycode == XK_Up)
		keys->up = input;
	if (keycode == XK_Down)
		keys->down = input;
	return (0);
}

int	pressed_key(int keycode, void *param)
{
	t_keys	*keys;
	t_data	*data;

	data = (t_data *) param;
	if (keycode == XK_Escape)
		return (fdf_cleanup(data, data->param.pt));
	keys = &data->param.keys;
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
	else
		return(keys_cont(keycode, keys, 1));
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
	else
		return(keys_cont(keycode, keys, 0));
	return (0);
}

int	mouse_wheel(int keycode, int x, int y, void *param)
{
	t_data	*data;

	(void) x;
	(void) y;
	data = (t_data *) param;
	if (!data->param.view.pers)
	{
		if (keycode == DOWN && data->param.view.scale > 6)
			data->param.view.scale -= 5;
		else if (keycode == UP)
			data->param.view.scale += 5;
		return (0);
	}
	if (keycode == DOWN && data->param.view.focal > 6)
		data->param.view.focal -= 5;
	else if (keycode == UP)
		data->param.view.focal += 5;
	return (0);
}

//colour: 0x00RRGGBB
int	loop_me(t_data data)
{
	data.param.keys = (t_keys){.w = 0, .a = 0, .s = 0, .d = 0, .q = 0, .e = 0};

	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, clicked_x, &data);

	mlx_hook(data.win, KeyPress, KeyPressMask, pressed_key, &data);

	mlx_hook(data.win, KeyRelease, KeyReleaseMask, released_key, &data.param.keys);

	mlx_mouse_hook(data.win, mouse_wheel, &data);

	mlx_loop_hook(data.mlx, draw_frame, &data);

	mlx_loop(data.mlx);

	return (0);
}
