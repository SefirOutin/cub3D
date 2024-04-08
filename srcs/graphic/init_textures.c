/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:18:42 by soutin            #+#    #+#             */
/*   Updated: 2024/04/08 15:48:54 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	str_error(char **tab, int i)
{
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

void	init_textures(t_data *data)
{
	int	i;

	i = -1;
	while (data->main.textures_path[++i])
	{
		data->main.textures[i].img = mlx_xpm_file_to_image(data->win.mlx_ptr,
				data->main.textures_path[i], &data->main.textures[i].w,
				&data->main.textures[i].h);
		if (!data->main.textures[i].img)
		{
			print_err("Image not initialised");
			free_imgs_error(data, data->main.textures, i);
			(str_error(data->main.textures_path, i), exit_and_free(data));
		}
		if (data->main.textures[i].h != 64 || data->main.textures[i].w != 64)
		{
			print_err("Image size not good");
			(str_error(data->main.textures_path, i), exit_and_free(data));
		}
		free(data->main.textures_path[i]);
		data->main.textures[i].addr
			= (int *)mlx_get_data_addr(data->main.textures[i].img,
				&data->main.textures[i].bpp, &data->main.textures[i].line_l,
				&data->main.textures[i].endian);
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
			"./asset/map_asset/player.xpm", &j, &j);
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
			(free_static_tab(data->main.textures_path), exit_and_free(data));
		}
		i++;
	}
}

void	init_asset(t_img *asset, t_data *data)
{
	asset[0].img = mlx_new_image(data->win.mlx_ptr, 15, 15);
	asset[1].img = mlx_new_image(data->win.mlx_ptr, 15, 15);
	asset[2].img = mlx_new_image(data->win.mlx_ptr, 15, 15);
	asset[0].addr = (int *)mlx_get_data_addr(data->minimap.textures[3],
			&(asset[0].bpp), &(asset[0].line_l), &(asset[0].endian));
	asset[1].addr = (int *)mlx_get_data_addr(data->minimap.textures[4],
			&(asset[1].bpp), &(asset[1].line_l), &(asset[1].endian));
	asset[2].addr = (int *)mlx_get_data_addr(data->minimap.textures[5],
			&(asset[2].bpp), &(asset[2].line_l), &(asset[2].endian));
}
