//#include "mlx_linux/mlx.h"
#include "ras.h"

float	rad(float n)
{
	return (n * (M_PI / 180.0));
}

//input 3 float output 2 float
//x stores vertical movement, y stores sideways movement
void	do_isometric(float *dst, t_fl fl, t_angle angle)
{
	float	x;
	float	y;
	float	z1;
	float	z2;
	float	f;

	x = (rad(fl.x) * cosf(rad(angle.x))) + (rad(fl.z) * sinf(rad(angle.x)));
	z1 = (-rad(fl.x) * sinf(rad(angle.x))) + (rad(fl.z) * cosf(rad(angle.x)));
	y = (rad(fl.y) * cosf(rad(angle.y))) - (rad(fl.z) * sinf(rad(angle.y)));//vertical is 35 ig
	z2 = (rad(fl.y) * sinf(rad(angle.y))) + (rad(fl.z) * cosf(rad(angle.y)));
	f = angle.p / (angle.p + z2);//arbitrary strength of perspective 300
	dst[0] = x * f;
	dst[1] = y * f;
}

void	set_at_zero(float p3d[8][3], float h, float t)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		p3d[i][0] = 0;
		p3d[i][1] = 0;
		p3d[i++][2] = 0;
	}
	p3d[1][0] = t;
	p3d[2][0] = t;
	p3d[2][1] = h;
	p3d[3][1] = h;
	p3d[4][2] = t;
	p3d[5][0] = t;
	p3d[5][2] = t;
	p3d[6][0] = t;
	p3d[6][1] = h;
	p3d[6][2] = t;
	p3d[7][1] = h;
	p3d[7][2] = t;
}

int	main(void)
{
	float	H = 10.0;
	float	T = 2.0;

	float	p3d[8][3];
	float	p2d[8][2];
	set_at_zero(p3d, H, T);
	int i = 0;
	while (i < 8)
	{
		do_isometric(*p2d[i], p3d[i], angle);
		i ++;
	}
