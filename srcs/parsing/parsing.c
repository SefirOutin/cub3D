#include "cub3d.h"
#include <stdio.h>

int	parsing(t_data *data, char *path)
{
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(&data->player, 0, sizeof(t_player));
	if (get_map_data(data, path) < 0)
		return (1);
	if (check_map(data))
		return (1);
	find_player(data);
	// if (data->img.x_max * 50 > 1200)
	// 	return (print_err("Map too big"), 1);
	return (0);
}
