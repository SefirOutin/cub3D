#include "cub3d.h"
#include <stdio.h>

void	init_img(t_data *data)
{
	int	i;

	i = 0;
	data->img.texture_map[0] = mlx_xpm_file_to_image(data->mlx_ptr,
														"./asset/map_asset/wall.xpm",
														&(data->img.size_x),
														&(data->img.size_y));
	data->img.texture_map[1] = mlx_xpm_file_to_image(data->mlx_ptr,
														"./asset/map_asset/player.xpm",
														&(data->img.size_x),
														&(data->img.size_y));
	data->img.texture_map[2] = mlx_xpm_file_to_image(data->mlx_ptr,
														"./asset/map_asset/floor.xpm",
														&(data->img.size_x),
														&(data->img.size_y));
	while (i < 3)
	{
		if (data->img.texture_map[i] == NULL)
		{
			write(2, "Error\nImage no initialised", 26);
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
void	fill_player_direction(t_data *data, int c)
{
	if (c == 'N')
	{
		data->player.direction = PI /2;
	}
	if (c == 'S')
	{
		data->player.direction = 3 * PI / 2;
	}
	if (c == 'W')
	{
		data->player.direction = PI;
	}
	if (c == 'E')
	{
		data->player.direction = 0;
	}
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (ft_strchr("NWSE", data->map[j][i]))
			{
				fill_player_direction(data, data->map[j][i]);
				data->player.px = i * 50;
				data->player.py = j * 50;
				return ;
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
						data->img.texture_map[0], (i * data->img.size_x),
						(j * data->img.size_y));
			if (data->map[j][i] == '0' || data->map[j][i] == 'N')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
						data->img.texture_map[2], (i * data->img.size_x),
						(j * data->img.size_y));
			i++;
		}
		i = 0;
		j++;
	}
}
