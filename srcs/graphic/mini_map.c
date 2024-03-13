/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:18:42 by soutin            #+#    #+#             */
/*   Updated: 2024/03/13 22:58:35 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mnmap_textures(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->mnmap.textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/wall.xpm", &(data->mnmap.size),
			&(data->mnmap.size));
	data->mnmap.textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/floor.xpm", &(data->mnmap.size),
			&(data->mnmap.size));
	data->mnmap.textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/player.xpm", &(data->mnmap.size),
			&(data->mnmap.size));
	data->mnmap.textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/map_wall.xpm", &j, &j);
	data->mnmap.textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/map_floor.xpm", &j, &j);
	data->mnmap.textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/map_player.xpm", &j, &j);
	while (i < 5)
	{
		if (data->mnmap.textures[i] == NULL)
		{
			write(2, "Error\nImage no initialised", 26);
			exit_and_free(data);
		}
		i++;
	}
}

void	get_player_data(t_data *data, int c, int i, int j)
{
	if (c == 'N')
	{
		data->player.direction = 90;
	}
	if (c == 'S')
	{
		data->player.direction = 270;
	}
	if (c == 'W')
	{
		data->player.direction = 180;
	}
	if (c == 'E')
	{
		data->player.direction = 0;
	}
	data->player.px = i * 50 + 25;
	data->player.py = j * 50 + 25;
	data->player_mini.px = i * 15 + 7;
	data->player_mini.px = j * 15 + 7;
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
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->mnmap.textures[0], (i * data->mnmap.size), (j
						* data->mnmap.size));
			if (ft_strchr("0NSWE", data->map[j][i]))
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->mnmap.textures[1], (i * data->mnmap.size), (j
						* data->mnmap.size));
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
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->mnmap.textures[1], (i * data->mnmap.size), (j
						* data->mnmap.size));
			i++;
		}
		j++;
	}
}
