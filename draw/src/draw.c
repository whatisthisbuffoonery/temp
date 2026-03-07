#include "h_mlx.h"

int	draw(t_map map, t_data data, t_3d *3d, t_2d *2d)//man I want int coords//convert from float vectors to int pixels before breisenham
{
	mlx_loop(data.mlx_ptr);
