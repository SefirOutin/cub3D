/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:52 by soutin            #+#    #+#             */
/*   Updated: 2024/03/15 18:25:24 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	init_img(t_data *data, int width, int height)
{
	t_img	img;
	
	img.img = mlx_new_image(data->win.mlx_ptr, width,
			height);
	if (!img.img)
		return (img);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.line_l, &img.endian);
	img.h = height;
	img.w = width;
	return (img);
}

