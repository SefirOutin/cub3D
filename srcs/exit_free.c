#include "cub3d.h"

int	exit_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	mlx_destroy_image_if_exists(data->mlx_ptr, data->textures[0]);
	mlx_destroy_image_if_exists(data->mlx_ptr, data->textures[1]);
	mlx_destroy_image_if_exists(data->mlx_ptr, data->textures[2]);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}