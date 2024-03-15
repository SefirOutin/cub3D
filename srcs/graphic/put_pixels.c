/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:12:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/14 18:49:05 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	background_img(t_img *img, int size, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_to_image(img, x++, y, color);
		}
		y++;
	}
}

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp / 8);
	((img->addr))[pixel_index / (int)(img->bpp / 8)] = color;
}

// void	put_circle_pixels(t_data *data, t_img *img, int point, int xx, int color)
// {
//     // put_pixel_to_image(img, xx, 25 - point, color);
//     // put_pixel_to_image(img, xx, 25 + point, color);
// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx, data->player.py - point,
// 			color);
// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx, data->player.py + point,
// 			color);
// 	// if (data->map[(int)(data->player.py - point) / 50][(int)xx / 50] == '1')
// 	// 	data->map[(int)(data->player.py - point) / 50][(int)xx / 50] = '5';
// 	// if (ft_strchr("0NSWE", data->map[(int)(data->player.py + point) / 50][(int)xx / 50]))
// 	// 	data->map[(int)(data->player.py + point) / 50][(int)xx / 50] = '6';
// }
