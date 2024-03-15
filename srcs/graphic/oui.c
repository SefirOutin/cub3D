/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/15 20:55:29 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp / 8);
	((img->addr))[pixel_index / (int)(img->bpp / 8)] = color;
}

int	view(t_data *data)
{
	int		x;
	double	y_top;
	double	y_bot;
	double	wall_height;
	int		half_height;
	int		ratio;
	int		i;

	ratio = data->win.w / data->main_img.nb_rays;
	// printf("w:%d\n", data->win.w);
	half_height = data->win.h * 0.5;
	data->main_img.view = init_img(data, data->win.w, data->win.h);
	x = 0;
	if (!data->main_img.view.img)
		return (1);
	while (x < data->win.w)
	{
		wall_height = data->win.h / data->main_img.rays_len[x / ratio] * 3;
		y_bot = half_height;
		y_top = half_height;
		while (wall_height--)
		{
			i = 0;
			while (i < ratio)
			{
				put_pixel_to_image(&data->main_img.view, x + i, y_bot, 0x0000FF);
		 		put_pixel_to_image(&data->main_img.view, x + i++, y_top, 0x0000FF);	
			}
			y_bot++;
			y_top--;
		}
		while (y_bot < data->win.h)
		{
			i = 0;
			while (i < ratio)
				put_pixel_to_image(&data->main_img.view, x + i++, y_bot,
						data->main_img.floor_color);
			y_bot++;
		}
		while (y_top > -1)
		{
			i = 0;
			while (i < ratio)
				put_pixel_to_image(&data->main_img.view, x + i++, y_top,
						data->main_img.ceilling_color);		
			y_top--;
		}
		x += ratio;
	}
	// mlx_destroy_image(data->mlx_ptr, data->main_img.view.img);
	return (0);
}
