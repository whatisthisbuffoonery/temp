#include "h_mlx.h"

int	data_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, v);
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);//i really really have to centralise cleanup
		return (1);
	}
	return (0);
}

void	int_arr_add(t_map *map, char *line, int *count, int *i)
{
	while (line[*i])
	{
		if (atoi_cond(line, *i))//another libft func woo //checks for valid '-' that has a number after
		{
			*count += 1;
			if (map->size < count && !ft_realloc(&map->arr, &map->size, sizeof(int)))//handles size *= 2
			{
				free(map->arr);//main does this already
				map->arr = NULL;
				return ;
			}
			map->arr[*count - 1] = ft_atoi_ind(&line[*i], *i);//this adds to i rather than reassign
		}
		*i += 1;
	}
}

int	map_init(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		map->row += 1;
		while (line[i] && count >= 0)
			int_arr_add(map, line, &count, &i);
		free(line);
		if (!map->arr)
			return (1);
		if (!map->col)
			map->col = map->count;
	}
	return (!map->arr);
}

//split rasterisation into (in order):
//rotation for x and y perspective
int	main(int c, char **v)
{
	t_3d	*3d;//these are all floats//eh use map size as saftey
	t_2d	*2d;
	t_map	map;
	int		fd;
	t_data	data;

	if (c != 2)
		return (1);
	fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return (1);
	map.arr = NULL;
	map.col = 0;
	map.row = 0;
	map.size = 0;
	map.diff = 0;
	if (map_init(&map, fd) || data_init(&data))
	{
		free(map.arr);//figure out cleanup, I wanna squeeze in 3d init
		return (1);
	}
	return (draw(map, data, 3d, 2d));//event loop cleanup go brrr
}
