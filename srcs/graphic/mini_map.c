#include "cub3d.h"
#include <stdio.h>

void	init_img(t_data *data)
{
	int	i;

	i = 0;
	data->texture_map[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/wall.xpm", &(data->size_ximg),
			&(data->size_yimg));
	data->texture_map[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/player.xpm", &(data->size_ximg),
			&(data->size_yimg));
	data->texture_map[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/floor.xpm", &(data->size_ximg),
			&(data->size_yimg));
	while (i < 3)
	{
		if (data->texture_map[i] == NULL)
		{
			write(2, "Error\nImage no initialise", 26);
			exit_and_free(data);
		}
		i++;
	}
}

void	erase_square(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + j, y + i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	put_square(int x, int y, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + j, y + i, 0xD35400);
			j++;
		}
		i++;
	}
}

void	dislay_player(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N')
			{
				data->pos_px = i * 50;
				data->pos_py = j * 50;
				put_square(data->pos_px, data->pos_py, data);
			}
			i++;
		}
		j++;
	}
}

void	display_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture_map[0], (i * 50), (j * 50));
			if (data->map[j][i] == '0' || data->map[j][i] == 'N')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->texture_map[2], (i * 50), (j * 50));
			i++;
		}
		i = 0;
		j++;
	}
}
