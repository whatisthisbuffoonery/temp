#ifndef H_MLX_H
# define H_MLX_H

# include "libft.h"
# include "mlx.h"
# include "X.h"

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef HEIGHT
#  define HEIGHT 600
# endif

typedef struct
{
	float	x;
	float	y;
}			t_angle;

//we will scale in ras
typedef struct
{
	int		x;
	int		y;
	int		z;
	float	fx;
	float	fy;//fml
}			t_pt;
//i made t map a dynamic array, i would want to just use this struct instead

typedef struct
{
	t_angle	angle;
	t_pt	*pt;
}			t_param;

typedef struct
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*buf;
	int				endian;//not a ptr oml
	int				line;
	int				bpp;
	int				x;//pls 0 index
	int				y;//we just sub one.......for two lines
	int				z_min;
	int				z_max;
	float			ax;//perspective
	float			ay;
	t_param			param;
}					t_data;
//bpp = 32
//line size = screen width
//endian: mlx_get_data_addr() sets &endian, use that
