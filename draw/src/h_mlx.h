#ifndef H_MLX_H
# define H_MLX_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysymdef.h>
# include <sys/time.h>

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef HEIGHT
#  define HEIGHT 600
# endif

# define SECOND_MCS 1000000 //7 digits

# ifndef FRAMES
#  define FRAMES 30
# endif

# define FRAME_MCS (SECOND_MCS / FRAMES) + 1 //rounded up...to be considered

# define EPSILON 1e-6f //dang floats not knowing what 0 is
# define WHITE 0x00FFFFFF //hm

typedef struct
{
	float	x;
	float	y;
	float	scale;//fmlllllllll
}			t_view;

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
	t_angle	view;
	t_pt	*pt;
}			t_param;

typedef struct
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*buf;//changed back for portability, settle tabs later
	int				size;
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
	//t_pt			tmp;//gosh dangit
}					t_data;
