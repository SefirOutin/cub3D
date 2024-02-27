#include "cub3d.h"
#include <stdio.h>

int	parsing(t_data *vars, char *path)
{
	ft_memset(vars, 0, sizeof(t_data));
	ft_memset(&vars->player_move, 0, sizeof(t_player));
	if (get_map_data(vars, path) < 0)
		return (1);
	if (check_map(vars))
		return (1);
	return (0);
}
