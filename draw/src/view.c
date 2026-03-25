#include "h_mlx.h"

t_view	angle_init(void)//, t_pt *pt, int size)
{
	t_view	ret;
	float	rad;

	rad = M_PI / 180.0f;
	ret.x = 35.264f * rad;
	ret.y = 0.0f * rad;
	ret.z = 45.0f * rad;
	ret.sinx = sinf(ret.x);
	ret.siny = sinf(ret.y);
	ret.sinz = sinf(ret.z);
	ret.cosx = cosf(ret.x);
	ret.cosy = cosf(ret.y);
	ret.cosz = cosf(ret.z);
	ret.scale = 1.0f;
	ret.step = M_PI / 180.0f;
	ret.rad_max = 2 * M_PI;
	return (ret);
}
