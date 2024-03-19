/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:18:42 by soutin            #+#    #+#             */
/*   Updated: 2024/03/19 18:53:59 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap_textures(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->minimap.textures[0] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/wall.xpm", &(data->minimap.size),
			&(data->minimap.size));
	data->minimap.textures[1] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/floor.xpm", &(data->minimap.size),
			&(data->minimap.size));
	data->minimap.textures[2] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/player.xpm", &(data->minimap.size),
			&(data->minimap.size));
	data->minimap.textures[3] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/map_wall.xpm", &j, &j);
	data->minimap.textures[4] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/map_floor.xpm", &j, &j);
	data->minimap.textures[5] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/map_player.xpm", &j, &j);
	while (i < 5)
	{
		if (data->minimap.textures[i] == NULL)
		{
			write(2, "Error\nImage no initialised", 26);
			exit_and_free(data);
		}
		i++;
	}
}

void	get_player_data(t_data *data, int c, int x, int y)
{
	if (c == 'N')
	{
		data->player.direction = 90 << SHIFT_AMOUNT;
	}
	if (c == 'S')
	{
		data->player.direction = 270 << SHIFT_AMOUNT;
	}
	if (c == 'W')
	{
		data->player.direction = 180 << SHIFT_AMOUNT;
	}
	if (c == 'E')
	{
		data->player.direction = 0 << SHIFT_AMOUNT;
	}
	data->player.pos.x = double_to_fixed(x + 0.5);
	data->player.pos.y = double_to_fixed(y + 0.5);
	data->player_mini.pos.x = x * 15 + 7;
	data->player_mini.pos.y = y * 15 + 7;
	printf("player x:%f y:%f\n", fixed_to_double(data->player.pos.x), fixed_to_double(data->player.pos.y));
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
				get_player_data(data, data->map[j][i], i, j);
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

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
					data->minimap.textures[0], (i * data->minimap.size), (j
						* data->minimap.size));
			if (ft_strchr("0NSWE", data->map[j][i]))
				mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
					data->minimap.textures[1], (i * data->minimap.size), (j
						* data->minimap.size));
			i++;
		}
		j++;
	}
}

void	erase_floors(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (ft_strchr("0NSWE", data->map[j][i]))
				mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
					data->minimap.textures[1], (i * data->minimap.size), (j
						* data->minimap.size));
			i++;
		}
		j++;
	}
}
