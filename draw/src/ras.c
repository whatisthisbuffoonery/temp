#include "h_mlx.h"

//rad all the angles first // see if you can squeeze fixed in here
//plez do not modify 3d array, do z scaling using local t_3d to call this //scale is determined at init
// no nevermind we have to include separate controls for both z and scale
//YX euler approach using left handed formula
//have a pixelset() func that checks for out-of-screen pixels
void	ras(t_3d *3d, t_2d *2d, t_angle angle, float scale)
{
	float	z;

	2d->x = (3d->x * cosf(angle.y)) + (3d->z * sinf(angle.y));
	z = -(3d->x * sinf(angle.y)) + (3d->z * cosf(angle.y));
	2d->y = (3d->y * cosf(angle.x)) + (3d->z * sinf(angle.x));
	//x = x * cos(angle.y) - z * sin(angle.y)
	//z = x * sin(angle.y) + z * cos(angle.y)
	2d->x *= scale;
	2d->y *= scale;
}
