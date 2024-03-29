/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:18:42 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 15:23:35 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_data *data)
{
	int i;

	i = 0;
	while (data->main.textures_path[i])
	{
		data->main.textures[i].img = mlx_xpm_file_to_image(data->win.mlx_ptr,
			data->main.textures_path[i], &data->main.textures[i].w,
			&data->main.textures[i].h);
		if (!data->main.textures[i].img)
		{
			print_err("Image not initialised");
			free_imgs_error(data, data->main.textures, i);
			exit_and_free(data);
		}
		free(data->main.textures_path[i]);
		if (data->main.textures[i].h != 64 || data->main.textures[i].w != 64)
		{
			print_err("Image not good");
			exit_and_free(data);
		}
		data->main.textures[i].addr = 
			(int *)mlx_get_data_addr(data->main.textures[i].img,
			&data->main.textures[i].bpp, &data->main.textures[i].line_l,
			&data->main.textures[i].endian);
		i++;
	}
}

void	init_minimap_textures(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->minimap.textures[0] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/wall.xpm", &j, &j);
	data->minimap.textures[1] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/floor.xpm", &j, &j);
	data->minimap.textures[2] = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"./asset/map_asset/player.xpm", &j,	&j);
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
			print_err("Image no initialised");
			exit_and_free(data);
		}
		i++;
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
