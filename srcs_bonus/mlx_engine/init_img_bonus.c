/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:52 by soutin            #+#    #+#             */
/*   Updated: 2024/03/16 14:08:45 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_img(t_data *data, t_img *img, int width, int height)
{
	img->img = mlx_new_image(data->win.mlx_ptr, width, height);
	if (!img->img)
		return (-1);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_l,
			&img->endian);
	img->h = height;
	img->w = width;
	return (0);
}
