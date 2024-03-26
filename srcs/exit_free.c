/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:08 by soutin            #+#    #+#             */
/*   Updated: 2024/03/26 17:48:11 by soutin           ###   ########.fr       */
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
	// int i;

	// i = 0;
	ft_free_tab(data->map);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.asset[0].img);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.asset[1].img);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.asset[2].img);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[0]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[1]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[2]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[3]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[4]);
	mlx_destroy_image(data->win.mlx_ptr, data->minimap.textures[5]);
	mlx_destroy_image(data->win.mlx_ptr, data->main.textures[0].img);
	mlx_destroy_image(data->win.mlx_ptr, data->main.textures[1].img);
	mlx_destroy_image(data->win.mlx_ptr, data->main.textures[2].img);
	mlx_destroy_image(data->win.mlx_ptr, data->main.textures[3].img);
	// mlx_destroy_image(data->win.mlx_ptr, data->main.textures[4].img);
	if (data->win.win_ptr)
		mlx_destroy_window(data->win.mlx_ptr, data->win.win_ptr);
	if (data->win.mlx_ptr)
	{
		mlx_destroy_display(data->win.mlx_ptr);
		free(data->win.mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}
