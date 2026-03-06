//#include "mlx_linux/mlx.h"
#include "ras.h"

float	rad(float n)
{
	return (n * (M_PI / 180.0));
}

//input 3 float output 2 float
//x is sideways, y is up and down
void	do_isometric(float *dst, t_fl fl, t_angle angle)
{
	float	x;
	float	y;
	float	z1;
	float	z2;
	float	f;

	x = (fl.x * cosf(rad(angle.x))) + (fl.z * sinf(rad(angle.x)));
	z1 = (-fl.x * sinf(rad(angle.x))) + (fl.z * cosf(rad(angle.x)));
	y = (fl.y * cosf(rad(angle.y))) - (z1 * sinf(rad(angle.y)));//vertical is 35 ig
	z2 = (fl.y * sinf(rad(angle.y))) + (z1 * cosf(rad(angle.y)));
	f = angle.p / (angle.p + z2);//arbitrary strength of perspective 300
	dst[0] = x * f;
	dst[1] = y * f;
}

void	set_at_zero(t_fl p3d[8], float h, float t)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		p3d[i].x = 0;
		p3d[i].y = 0;
		p3d[i++].z = 0;
	}
	p3d[1].x = t;
	p3d[2].x = t;
	p3d[2].y = h;
	p3d[3].y = h;
	p3d[4].z = t;
	p3d[5].x = t;
	p3d[5].z = t;
	p3d[6].x = t;
	p3d[6].y = h;
	p3d[6].z = t;
	p3d[7].y = h;
	p3d[7].z = t;
}

char	me_round(float s[8][2], int n)
{
	float f;
	int i = 0;

	while (i < 8)
	{
		f = s[i][0] - n;
		if (((f <= 0.5) && (f >= -0.5))) 
			return ('1');
		f = s[i][1] - n;
		if (((f <= 0.5) && (f >= -0.5))) 
			return ('1');
		i ++;
	}
	return ('0');
}

void ft_putnbr(int src)
{
	unsigned int t = 1;
	unsigned int n = src;
	char a;

	if (src < 0)
	{
		write(1, "-", 1);
		n = 0 - src;
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
}

int scale(float f, int pad)
{
	float f1 = f * 5;
	int n = f1 + pad;
	return (n);
}

int	main(void)
{
	float	H = 2.0;
	float	T = 2.0;

	t_fl	p3d[8];
	float	p2d[8][2];
	set_at_zero(p3d, H, T);
	int i = 0;
	t_angle angle = {.x = 45.0, .y = 35.264, .p = 0.0};
	while (i < 8)
	{
		do_isometric(p2d[i], p3d[i], angle);
		i ++;
	}
	i = 0;
	int fd = open("heh", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	/*
	while (i < lim)
	{
		res =  me_round(p2d, i);
		write(fd, &res, 1);
		if (i % 10 == 9)
			write(fd, "\n", 1);
		i ++;
	}
	*/
	int n[16];
	//i = 0;
	while (i < 8)
	{
		n[(2 * i)] = scale(p2d[i][0], 2);
		n[(2 * i) + 1] = scale(p2d[i][1], 30);
		i ++;
	}
	i = 0;
	char buf[10000];
	while (i < 10000)
		buf[i++] = ' ';
	i = 0;
	while (i < 16)
	{
		ft_putnbr(n[i]);
		write(1, " ", 1);
		if (i % 2)
			buf[(n[i] * 64) + n[i - 1]] = '1';
		i ++;
	}
	write(1, "\n", 1);
	i = 0;
	while (i < 8)
	{
		printf("%f, %f\n", p2d[i][0], p2d[i][1]);
		i ++;
	}
	i = 0;
	while (i < 4096)
	{
		write(fd, &buf[i], 1);
		if (i % 64 == 63)
			write(fd, "e\n", 2);
		i ++;
	}
	close(fd);
}
