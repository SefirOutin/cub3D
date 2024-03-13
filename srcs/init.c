/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:52:51 by soutin            #+#    #+#             */
/*   Updated: 2024/03/13 22:57:44 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, (data->mnmap.x_max + 1) * 50,
			(data->mnmap.y_max + 1) * 50, "MazeCub3D");
	if (!data->win_ptr)
		return (free(data->win_ptr), 1);
	init_mnmap_textures(data);
	init_asset(data->asset,data);
	data->mnmap.size = 50;
	return (0);
}


void	init_hook_and_loop(t_data *data)
{
	// mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, mouse, data),
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, release_inputs, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, get_inputs, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
			data);
	mlx_loop_hook(data->mlx_ptr, on_keypress, data);
	mlx_loop(data->mlx_ptr);

}
t_img	init_img(t_data *data, int size_x, int size_y)
{
	t_img	img;
	
	img.img = mlx_new_image(data->mlx_ptr, size_x,
			size_y);
	if (!img.img)
		return (img);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.line_l, &img.endian);
	return (img);
}
