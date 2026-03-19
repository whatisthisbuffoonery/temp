#include "h_mlx.h"

int	size_init(t_data *data, int fd)
{
	char	*line;
	int		i;
	int		count;

	i = 0;
	count = 0;
	line = gnl(fd);
	while (line)
	{
		if ((!i && ft_isdigit(line[i]))
			|| (line[i] && !ft_isdigit(line[i]) && ft_isdigit(line[i + 1]))) //catches negative numbers
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

int	pt_xy(t_pt **pt, t_data *data)
{
	int	i;
	int	line;

	i = 0;
	line = data->x + 1;
	while (i < data->size)
	{
		(*pt)[i].x = i % line;
		(*pt)[i].y = i / line;
		i ++;
	}
	return (0);
}

int	pt_init(t_pt **pt, t_data *data, int *fd)
{
	int		i;
	int		k;
	char	*line;

	i = 0;
	k = 0;
	data->size = size_init(data, fd[0]);
	line = gnl(fd[1]);
	if (data->size < 1 || !malloc_cond((void **) pt, data->size * sizeof(t_pt)))
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
		return (1);
	data->bypp = data->bipp / 8;
	data->ubuf = (unsigned int *) data->buf;
	if (data->bipp == 32)
		data->buf_edit = buf_edit_uint;
	else
		data->buf_edit = buf_edit_char;
	return (0);
}

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
	free(data.mlx);
	d->mlx = NULL;
	d->win = NULL;
	d->img = NULL;
	d->buf = NULL;
	d->param.pt = NULL;
	exit(0);
	return (1);
}

int	main(int c, char **v)
{
	t_pt	*pt;
	t_data	data;
	int		fd[2];

	if (c != 2 || fd_init(v[1], fd))//sorry, could not finish perspective projection in time, c != 2 it is.
		return (1);
	
	ft_memset(&data, 0, sizeof(t_data));
	if (pt_init(&pt, &data, fd) || data_init(&data, v[1]))
		return (fdf_cleanup(&data, pt));
	data.y -= 1;//0 index
	close(fd[0]);
	close(fd[1]);
	data.param.pt = pt;
	view_init(pt, data.size, v, &data);

	return (loop_me(data));
}
