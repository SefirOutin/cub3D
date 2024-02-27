#include "cub3d.h"

void	mlx_destroy_image_if_exists(void *mlx_ptr, void *img)
{
	if (img)
		mlx_destroy_image(mlx_ptr, img);
}

int	exit_and_free(t_data *data)
{
	int i;

	i = 0;
	ft_free_tab(data->map);
	free(data->textures[0]);
	free(data->textures[1]);
	free(data->textures[2]);
	free(data->textures[3]);
	mlx_destroy_image_if_exists(data->mlx_ptr, data->texture_map[0]);
	mlx_destroy_image_if_exists(data->mlx_ptr, data->texture_map[1]);
	mlx_destroy_image_if_exists(data->mlx_ptr, data->texture_map[2]);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}