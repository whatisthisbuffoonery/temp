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
			|| (line[i] && !ft_isdigit(line[i]) && ft_isdigit(line[i + 1])))
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

int	pt_xyz(t_pt **pt, t_data *data)
{
	int	i;
	int	line;
	int	z_min;
	int	z_max;

	i = 0;
	z_min = INT_MAX;
	z_max = INT_MIN;
	line = data->x + 1;
	while (i < data->size)
	{
		(*pt)[i].x = i % line;
		(*pt)[i].y = i / line;
		if ((*pt)[i].z < z_min)
			z_min = (*pt)[i].z;
		if ((*pt)[i].z > z_max)
			z_max = (*pt)[i].z;
		i ++;
	}
	data->f = max2(abs(z_min), abs(z_max)) * 2.0f;
	return (0);
}

int	fd_err(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (1);
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
		return (fd_err(fd));
	while (line)
	{
		if ((ft_isdigit(line[i]))
			|| (line[i] == '-' && ft_isdigit(line[i + 1])))
			(*pt)[k++].z = ft_atoi_ind(&line[i], &i);
		i += (line[i] != 0);
		if (!line[i])
		{
			i = 0;
			free(line);
			line = gnl(fd[1]);
		}
	}
	return (pt_xyz(pt, data));
}
