#include "h_mlx.h"

t_view	angle_init(char **v)//, t_pt *pt, int size)
{
	t_view	ret;

	if (v[2] && v[2][0] == 'p' && v[2][1] == '\0')
		ret.pers = 1;
	else
		ret.pers = 0;
	(void) v;
	ret.x = (360.0f - 35.264f) * RAD;
	ret.y = 0.0f * RAD;
	ret.z = (360.0f - 45.0f) * RAD;
	ret.sinx = sinf(ret.x);
	ret.siny = sinf(ret.y);
	ret.sinz = sinf(ret.z);
	ret.cosx = cosf(ret.x);
	ret.cosy = cosf(ret.y);
	ret.cosz = cosf(ret.z);
	ret.fov = 60.0f; /* degrees */
    ret.focal = ((float)HEIGHT * 0.5f) / tanf((ret.fov * 0.5f) * RAD);
	return (ret);
}
