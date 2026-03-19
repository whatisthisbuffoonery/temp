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
#  define FRAMES 60
# endif

# define FRAME_MCS ((SECOND_MCS / FRAMES) + 1)

# define EPSILON 1e-6f
# define R_PI (2 * M_PI)
# define DEG (180.0f / M_PI)
# define RAD (M_PI / 180.0f)
# define STEP (1.0f * RAD)
# define RAD_MAX (360.0f * RAD)

# define SHADE 0x00010101

# define UP 4
# define DOWN 5

typedef struct
{
	float	x;
	float	y;
	float	z;
	float	scale;
	float	cosx;
	float	sinx;
	float	cosy;
	float	siny;
	float	cosz;
	float	sinz;
	float	fov;
	float	focal;
	char	pers;
}			t_view;

//we will scale in ras
typedef struct
{
	int		x;
	int		y;
	int		z;
	float	fx;
	float	fy;
	float	fz;
}			t_pt;

typedef struct
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	q;
	char	e;
	char	up;
	char	left;
	char	down;
	char	right;
}			t_keys;

typedef struct
{
	t_view	view;
	t_pt	*pt;
	t_keys	keys;
}			t_param;

typedef struct
{
	float	xu;
	float	xl;
	float	yu;
	float	yl;
	float	zu;
	float	zl;
	float	cx;
	float	cy;
	float	cz;
}			t_lim;

typedef struct
{
	float	x;
	float	y;
	float	z;
}			t_trig;


typedef struct s_data
{
	t_param			param;
	void			*mlx;
	void			*win;
	void			*img;
	char			*buf;
	unsigned int	*ubuf;
	void			(*buf_edit)(struct s_data *, float, float);
	int				size;
	int				endian;
	int				line;
	int				bipp;
	int				bypp;
	unsigned int	colour_max;
	int				x;
	int				y;
	float			cx;
	float			cy;
	float			cz;
	float			offset_x;
	float			offset_y;
}					t_data;

void	view_init(t_pt *pt, int size, char **v, t_data *data);
t_view	angle_init(char **v);

void	buf_edit_uint(t_data *data, float fx, float fy);
void	buf_edit_char(t_data *data, float fx, float fy);
void	rasterise(t_pt *pt, t_view view, int size, t_data *data);
void	xiaolin_wu(t_pt src, t_pt dst, t_data *data);
void	goodlines(t_data *data);
void	change_view(t_view *view, t_keys keys);
int		frame_wait(struct timeval start);
int		loop_me(t_data data);
int		fdf_cleanup(t_data *d, t_pt *pt);
int		draw_frame(void *param);

#endif
