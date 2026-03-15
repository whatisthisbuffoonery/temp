#include "h_mlx.h"

//rad all the angles first // see if you can squeeze fixed in here
//plez do not modify 3d array, do z scaling using local t_3d to call this //scale is determined at init
// no nevermind we have to include separate controls for both z and scale
//actually handle scale AFTER this func

//YX euler approach using left handed formula

//have a pixelset() func that checks for out-of-screen pixels
//x = x * cos(angle.y) - z * sin(angle.y)
//z = x * sin(angle.y) + z * cos(angle.y)
//scale separately

float	scale_init(t_pt *pt, int size)
{
	float	x_max;
	float	y_max;
	float	x_min;
	float	y_min;
	int		i;

	x_min = INT_MAX;
	y_min = INT_MAX;
	x_max = INT_MIN;
	y_max = INT_MIN;
	i = 0;
	while (i < size)
	{
		if (pt[i].fx > x_max)
			x_max = pt[i].fx;
		if (pt[i].fy > y_max)
			y_max = pt[i].fy;
		if (pt[i].fx < x_min)
			x_min = pt[i].fx;
		if (pt[i].fy < y_min)
			y_min = pt[i].fy;
		i ++;
	}
	return (fminf(WIDTH / fabs(x_max - x_min), HEIGHT / fabs(y_max - y_min)));
}

t_view	view_init(t_pt *pt, int size, char **v)
{
	float	z;
	int		i;
	t_view	view;

	view = angle_init(v);//pls cast to rad
	i = 0;
	while (i < size)
	{
		pt[i].fx = (pt[i].x * cosf(view.y)) + (pt[i].z * sinf(view.y));
		z = -(pt[i].x * sinf(view.y)) + (pt[i].z * cosf(view.y));
		pt[i].fy = (pt[i].y * cosf(view.x)) + (pt[i].z * sinf(view.x));
		i ++;
	}
	view.scale = scale_init(pt, size);
	i = 0;
	while (i < size)
	{
		pt[i].fx *= scale;
		pt[i].fy *= scale;
		i ++;
	}
	return (view);
}

//((x * cos) + (y * sin)) * scale
//
void	rasterise_isometric(t_pt *pt, t_view view, int size)
{
	float	z;
	int		i;

	i = 0;
	while (i < size)//get key changer to calc sin and cos, store another copy with scale included (i.e. cos * scale)
	{
		pt[i].fx = ((pt[i].x * cosf(view.y)) + (pt[i].z * sinf(view.y))) * view.scale;
		z = -(pt[i].x * sinf(view.y)) + (pt[i].z * cosf(view.y));
		pt[i].fy = ((pt[i].y * cosf(view.x)) + (pt[i].z * sinf(view.x))) * view.scale;
		i ++;
	}
}

void	parallel()
{
	///wtf
}
