#include "h_mlx.h"

t_view	angle_init(char **v)//, t_pt *pt, int size)
{
	t_view	ret;

	(void) v;
//	ir_set(&x, *y, NULL, NULL);
	ret.x = (35.264f) * RAD;
	ret.y = (45.0f) * RAD;
	ret.sinx = sinf(ret.x);
	ret.siny = sinf(ret.y);
	ret.cosx = cosf(ret.x);
	ret.cosy = cosf(ret.y);
	return (ret);
}
