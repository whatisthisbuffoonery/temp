#ifndef H_MLX_H
# define H_MLX_H

# include "mlx.h"
# include <math.h>
# include <float.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include "libft.h"
# include "get_next_line.h"

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef HEIGHT
#  define HEIGHT 600
# endif

# define SECOND_MCS 1000000 //7 digits

# ifndef FRAMES
#  define FRAMES 10
# endif

# define FRAME_MCS ((SECOND_MCS / FRAMES) + 1) //rounded up...to be considered

# define EPSILON 1e-6f //dang floats not knowing what 0 is
# define WHITE 0x00FFFFFF //hm
# define R_PI (2 * M_PI)
# define DEG (180.0f / M_PI)
# define RAD (M_PI / 180.0f)
# define STEP (1.0f * RAD)
# define RAD_MAX (360.0f * RAD)

# define UP 4
# define DOWN 5

typedef struct
{
	float	x;
	float	y;
	float	scale;//fmlllllllll
	float	cosx;
	float	sinx;
	float	cosy;
	float	siny;
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
	char	w;
	char	a;
	char	s;
	char	d;
}			t_keys;

typedef struct//to phase out
{
	t_view	view;
	t_pt	*pt;
	t_keys	keys;
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
	int				bipp;
	int				bypp;
	int				x;//pls 0 index
	int				y;//we just sub one.......for two lines
	float			ax;//perspective
	float			ay;
	t_param			param;
	//t_pt			tmp;//gosh dangit
}					t_data;

t_view	view_init(t_pt *pt, int size, char **v);
t_view	angle_init(char **v);

void	rasterise(t_pt *pt, t_view view, int size);
void	xiaolin_wu(t_pt src, t_pt dst, t_data *data);
void	goodlines(t_data *data);
void	change_view(t_view *view, t_keys keys);
int		frame_wait(struct timeval start);
int		loop_me(t_data data);
int		fdf_cleanup(t_data *d, t_pt *pt);
int		draw_frame(void *param);

#endif
