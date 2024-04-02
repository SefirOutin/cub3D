/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:52:51 by soutin            #+#    #+#             */
/*   Updated: 2024/03/30 15:47:00 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_display(t_data *data)
{
	create_rays(data);
	view(data);
	create_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
		data->main.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main.view.img);
}

int	init_mlx_data(t_data *data)
{
	data->win.mlx_ptr = mlx_init();
	if (!data->win.mlx_ptr)
		return (1);
	mlx_get_screen_size(data->win.mlx_ptr, &data->win.w, &data->win.h);
	data->win.h = 650;
	data->win.w = 640;
	data->win.win_ptr = mlx_new_window(data->win.mlx_ptr, data->win.w,
			data->win.h, "MazeCub3D");
	if (!data->win.win_ptr)
		return (free(data->win.win_ptr), 1);
	init_minimap_textures(data);
	init_asset(data->minimap.asset, data);
	init_textures(data);
	data->minimap.size = 50;
	data->main.nb_rays = 640;
	return (0);
}

void	init_hook_and_loop(t_data *data)
{
	mlx_hook(data->win.win_ptr, KeyRelease, KeyReleaseMask, release_inputs,
		data);
	mlx_hook(data->win.win_ptr, KeyPress, KeyPressMask, get_inputs, data);
	mlx_hook(data->win.win_ptr, DestroyNotify, StructureNotifyMask,
		&exit_and_free, data);
	mlx_loop_hook(data->win.mlx_ptr, on_keypress, data);
	mlx_loop(data->win.mlx_ptr);
}
