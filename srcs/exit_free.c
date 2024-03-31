/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:08 by soutin            #+#    #+#             */
/*   Updated: 2024/03/31 15:30:27 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_imgs_error(t_data *data, t_img *imgs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mlx_destroy_image(data->win.mlx_ptr, imgs[i++].img);
	}
}

int	exit_and_free(t_data *data)
{
	ft_free_tab(data->map);
	destroy_image(data->minimap.asset[0], data);
	destroy_image(data->minimap.asset[1], data);
	destroy_image(data->minimap.asset[2], data);
	destroy_image(data->main.textures[0], data);
	destroy_image(data->main.textures[1], data);
	destroy_image(data->main.textures[2], data);
	destroy_image(data->main.textures[3], data);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[0]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[1]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[2]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[3]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[4]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[5]);
	if (data->win.win_ptr)
		mlx_destroy_window(data->win.mlx_ptr, data->win.win_ptr);
	if (data->win.mlx_ptr)
	{
		mlx_destroy_display(data->win.mlx_ptr);
		free(data->win.mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}
