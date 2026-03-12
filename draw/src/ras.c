#include "h_mlx.h"

//rad all the angles first // see if you can squeeze fixed in here
//plez do not modify 3d array, do z scaling using local t_3d to call this //scale is determined at init
// no nevermind we have to include separate controls for both z and scale
//actually handle scale AFTER this func

//YX euler approach using left handed formula

//have a pixelset() func that checks for out-of-screen pixels
//x = x * cos(angle.y) - z * sin(angle.y)
//z = x * sin(angle.y) + z * cos(angle.y)
void	rasterise_isomnetric(t_pt *pt, t_angle angle, float scale)
{
	float	z;

	pt->fx = (pt->x * cosf(angle.y)) + (pt->z * sinf(angle.y));
	z = -(pt->x * sinf(angle.y)) + (pt->z * cosf(angle.y));
	pt->fy = (pt->y * cosf(angle.x)) + (pt->z * sinf(angle.x));
	pt->fx *= scale;
	pt->fy *= scale;
}

void	parallel()
{
	///wtf
}
