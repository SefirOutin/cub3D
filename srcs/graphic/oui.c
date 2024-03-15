/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/14 22:38:52 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	view(t_data *data)
{
	int		x;
	double		y;
	double	height;

	data->view = init_img(data, 1080, 360);
	x = 0;
    if (!data->view.img)
		return (1);
	while (x < 1080 - 3)
	{
        y = 360 * 0.5;
        height = 1200 / data->rays_len[x / 3];
		while (height)
        {
            put_pixel_to_image(&data->view, x, y, 0x0000FF);
            height--;
			put_pixel_to_image(&data->view, x + 1, y, 0x0000FF);
			put_pixel_to_image(&data->view, x + 2, y, 0x0000FF);
            y++;
        }
		while (y < 360)
		{
			put_pixel_to_image(&data->view, x, y, data->floor_color);
			put_pixel_to_image(&data->view, x + 1, y, data->floor_color);
			put_pixel_to_image(&data->view, x + 2, y, data->floor_color);
            y++;
		}
		y = 360 * 0.5;
	    height = 1200 / data->rays_len[x / 3];
        while (height > -1)
        {
            put_pixel_to_image(&data->view, x, y, 0x0000FF);
            height--;
			put_pixel_to_image(&data->view, x + 1, y, 0x0000FF);
			put_pixel_to_image(&data->view, x + 2, y, 0x0000FF);
            y--;
        }
		while (y > -1)
		{
			put_pixel_to_image(&data->view, x, y, data->ceilling_color);
			put_pixel_to_image(&data->view, x + 1 , y, data->ceilling_color);
			put_pixel_to_image(&data->view, x + 2, y, data->ceilling_color);
            y--;
		}
		
        
        x += 3;
	}  
	// mlx_destroy_image(data->mlx_ptr, data->view.img);
	return (0);
}