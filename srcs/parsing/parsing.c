#include "cub3d.h"
#include <stdio.h>

int	parsing(t_data *vars, char *path)
{
	// int	i;

	// i = 0;
	ft_memset(vars, 0, sizeof(t_data));
	ft_memset(&vars->player, 0, sizeof(t_player));
	// while (i < 6)
	// {
	// 	ft_memset(vars->player.inputs[i], 0, 2);
	// 	i++;
	// }
	if (get_map_data(vars, path) < 0)
		return (1);
	if (check_map(vars))
		return (1);
	find_player(vars);
	return (0);
}
