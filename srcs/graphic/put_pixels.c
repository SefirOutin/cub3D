/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:12:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/05 15:40:29 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_mlx_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp / 8);
	((img->addr))[pixel_index / (int)(img->bpp / 8)] = color;
}

void	put_circle_pixels(t_data *data, int point, int xx, int color)
{
    // put_pixel_to_image(img, xx, data->player.py - point, color);
    // put_pixel_to_image(img, xx, data->player.py + point, color);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx, data->player.py - point,
			color);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, xx, data->player.py + point,
			color);
	// if (data->map[(int)(data->player.py - point) / 50][(int)xx / 50] == '1')
	// 	data->map[(int)(data->player.py - point) / 50][(int)xx / 50] = '5';
	// if (ft_strchr("0NSWE", data->map[(int)(data->player.py + point) / 50][(int)xx / 50]))
	// 	data->map[(int)(data->player.py + point) / 50][(int)xx / 50] = '6';
}

void	mid_point_put_pixels(t_data *data, t_point current, int color)
{
    // put_pixel_to_image(img, current.x + data->player.px, current.y + data->player.py, color);
    // put_pixel_to_image(img, -current.x + data->player.px, current.y + data->player.py, color);
    // put_pixel_to_image(img, current.x + data->player.px, -current.y + data->player.py, color);
    // put_pixel_to_image(img, -current.x + data->player.px, -current.y + data->player.py, color);
    // if (current.x != current.y)
    // {
    //     put_pixel_to_image(img, current.y + data->player.px, current.x + data->player.py, color);
    //     put_pixel_to_image(img, current.y + data->player.px, -current.x + data->player.py, color);
    //     put_pixel_to_image(img, -current.y + data->player.px, current.x + data->player.py, color);
    //     put_pixel_to_image(img, -current.y + data->player.px, -current.x + data->player.py, color);
    // }
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.x + data->player.px,
			current.y + data->player.py, color);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.x + data->player.px,
			current.y + data->player.py, color);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.x + data->player.px,
			-current.y + data->player.py, color);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.x + data->player.px,
			-current.y + data->player.py, color);
	if (current.x != current.y)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.y + data->player.px,
				current.x + data->player.py, color);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.y + data->player.px,
				-current.x + data->player.py, color);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.y + data->player.px,
                current.x + data->player.py, color);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.y + data->player.px,
                -current.x + data->player.py, color);
	}
}
