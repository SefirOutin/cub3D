/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:52:51 by soutin            #+#    #+#             */
/*   Updated: 2024/03/15 20:54:54 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_data(t_data *data)
{
	data->win.mlx_ptr = mlx_init();
	if (!data->win.mlx_ptr)
		return (1);
	mlx_get_screen_size(data->win.mlx_ptr, &data->win.w, &data->win.h);
	data->win.win_ptr = mlx_new_window(data->win.mlx_ptr, data->win.w,
			data->win.h, "MazeCub3D");
	if (!data->win.win_ptr)
		return (free(data->win.win_ptr), 1);
	init_minimap_textures(data);
	init_asset(data->minimap.asset, data);
	data->minimap.size = 50;
	data->main_img.nb_rays = 640;
	return (0);
}


void	init_hook_and_loop(t_data *data)
{
	// mlx_hook(data->win.win_ptr, MotionNotify, PointerMotionMask, mouse, data),
	mlx_hook(data->win.win_ptr, KeyRelease, KeyReleaseMask, release_inputs, data);
	mlx_hook(data->win.win_ptr, KeyPress, KeyPressMask, get_inputs, data);
	mlx_hook(data->win.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
			data);
	mlx_loop_hook(data->win.mlx_ptr, on_keypress, data);
	mlx_loop(data->win.mlx_ptr);

}

