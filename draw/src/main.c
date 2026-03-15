#include "h_mlx.h"

int	size_init(t_data *data, int fd)//open files outside // start x from 0 we'll edit the padding later
{
	char	*line;
	int		i;
	int		count;

	i = 0;
	count = 0;//set data elsewhere
	line = gnl(fd);
	while (line)
	{
		if ((!i && ft_isdigit(line[i]))
			|| (!ft_isdigit(line[i]) && ft_isdigit(line[i + 1]))) //catches negative numbers
			count ++;
		if (!line[i])
		{
			i = 0;
			free(line);
			line = gnl(fd);
			data->y += 1;
			if (!data->x)
				data->x = count - 1;
		}
		else
			i ++;
	}
	return (count);
}

// we will open two fds for this

int	pt_xy(t_pt **pt, t_data *data)
{
	int	i;

	i = 0;
	data->z_min = INT_MAX;
	data->z_max = INT_MIN;
	while (i < data->size)
	{
		(*pt)[i].x = i % WIDTH;
		(*pt)[i].y = i / WIDTH;
		if ((*pt)[i].z < data->z_min)
			data->z_min = (*pt)[i].z;
		if ((*pt)[i].z > data->z_max)
			data->z_max = (*pt)[i].z;
		i ++;
	}
}

//i just realised my parsing is a bit overkill
int	pt_init(t_pt **pt, t_data *data, int *fd)
{
	int		fd[2];
	int		i;
	int		k;
	char	*line;

	i = 0;
	k = 0;
	data->size = size_init(data, fd[0]);
	line = gnl(fd[1]);
	if (!data->size || !malloc_cond(pt, data->size * sizeof(t_pt)))
		return (1);
	while (line)
	{
		if ((ft_isdigit(line[i])) || (line[i] == '-' && ft_isdigit(line[i + 1])))
			(*pt)[k++].z = ft_atoi_ind(&line[i], &i);
		i += (line[i] != 0);
		if (!line[i])
		{
			i = 0;
			free(line);
			line = gnl(fd[1]);
		}
	}
	return (pt_xy(pt, data));
}

//data file here
int	data_init(t_data *data, char *v)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, v);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img)
		data->buf = mlx_get_data_addr(data->img,
				&data->bipp,
				&data->line,
				&data->endian);
	if (!data->win || !data->img || !data->buf)
		return (1);//cleanup elsewhere
	data->bypp = data->bipp / 8;
	return (0);
}

void	set_all(t_data *data)
{
	t_data	d;

	d.mlx = NULL;
	d.win = NULL;
	d.img = NULL;
	d.buf = NULL;
	d.z_min = INT_MAX;
	d.z_max = INT_MIN;
	d.x = 0;
	d.y = 0;
	*data = d;
}

//main file
int	fd_init(char *v, int *fd)
{
	fd[0] = open(v, O_RDONLY);
	if (fd[0] < 0)
		return (1);
	fd[1] = open(v, O_RDONLY);
	if (fd[1] < 0)
	{
		close(fd[0]);
		return (1);
	}
	return (0);
}

int	fdf_cleanup(t_data *d, t_pt *pt)
{
	t_data	data;

	data = *d;
	free(pt);
	if (data.img)
		mlx_destroy_image(data.mlx, data.img);
	if (data.win)
		mlx_destroy_window(data.mlx, data.win);
	if (data.mlx)
		mlx_destroy_display(data.mlx);
	free(data.mlx);//damn you ai
	//exit(0);//bruh//fuck you, you barely passed
	return (1);
}

//split rasterisation into (in order):
//rotation for x and y perspective
int	main(int c, char **v)
{
	t_pt	*pt;//these are all floats//eh use map size as safety
	t_data	data;
	int		fd[2];

	if (c != 2 || fd_init(v[1], fd)) //diff for bonus projection, have angle init func here too
		return (1);
	pt = NULL;
	set_all(&data);
	if (pt_init(&pt, &data, fd) || data_init(&data, v[1]))
		return (fdf_cleanup(&data, pt));
	data.y -= 1;//0 index
	close(fd[0]);
	close(fd[1]);
	data.param.view = view_init(v, pt);
	data.param.pt = pt;
	return (loop_me(data));//angle and data are copied
}
