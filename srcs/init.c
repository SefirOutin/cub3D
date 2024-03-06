/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:52:51 by soutin            #+#    #+#             */
/*   Updated: 2024/03/02 16:47:03 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, (data->img.x_max + 1) * 50,
			(data->img.y_max + 1) * 50, "MazeCub3D");
	if (!data->win_ptr)
		return (free(data->win_ptr), 1);
	init_img(data);
	// data->player.direction = 0;
	data->img.size_x = 50;
	data->img.size_y = 50;
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
int	init_mlx_img(t_data *data)
{
	int	i;
	
	i = 0;
	data->image.img = mlx_new_image(data->mlx_ptr, data->img.x_max * 50,
			(data->img.y_max) * 50);
	if (!data->image.img)
		return (-1);
	data->image.addr = (int *)mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_l, &data->image.endian);
	while (data->image.addr[i])
		data->image.addr[i++] = 0xFFFFFF;
	return (0);
}