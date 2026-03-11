#include "h_mlx.h"

int	

//colour: 0x00RRGGBB
int	draw(t_data data, t_pt *pt, t_angle angle)//man I want int coords//convert from float vectors to int pixels before breisenham
{//change cleanup to non ptr
	t_param	param;

	param = {.angle = angle, .pt = pt};//put scale in angle//maybe put lims in angle too
	data.param = param;
	draw_frame(' ', param);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, clicked_x, data);//same func prototype as keypress
	mlx_hook(data.win, KeyPress, KeyPressMask, esc_key, data);
	mlx_hook(data.win, KeyPress, KeyPressMask, draw_frame, param);//calls scale and angle modifiers, then ras and brei
	mlx_loop(data.mlx_ptr);
	return (0);
}
