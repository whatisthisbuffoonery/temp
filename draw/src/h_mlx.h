#ifndef H_MLX_H
# define H_MLX_H

# include "libft.h"
# include "mlx.h"

typedef struct
{
	float	x;
	float	y;
}			t_2d;

//we will scale in ras
typedef struct
{
	int	x;
	int	y;
	int	z;
}		t_3d;
//i made t map a dynamic array, i would want to just use this struct instead

typedef struct
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*buf;
	int				*endian;
}					t_data;
//bpp = 32
//line size = screen width
//endian: mlx_get_data_addr() sets &endian, use that
