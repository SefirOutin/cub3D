/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:28:45 by soutin            #+#    #+#             */
/*   Updated: 2024/03/15 17:41:15 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void draw_xpm(t_data *data, double angle)
{
    t_img	img;
    int		color;
    int		x;
    int		y;

	y = 0;
    img.addr = (int *)mlx_get_data_addr(data->minimap.textures[2], &img.bpp, &img.line_l, &img.endian);
    while (y < 50)
	{
		x = 0;
		while (x < 50)
		{
            int new_x = round((x - 25) * cos(angle) + (y - 25) * sin(angle)) + data->player.pos.x;
            int new_y = round((x - 25) * sin(angle) + (y - 25) * cos(angle)) + data->player.pos.y;
            color = img.addr[y * 50 + x];
            if (color >= 0 && new_x >= 0 && new_x < 1920 && new_y >= 0 && new_y < 1080)
                mlx_pixel_put(data->win.mlx_ptr, data->win.win_ptr, new_x, new_y, color);
			x++;
		}
		y++;
	}
    // mlx_destroy_image(win.mlx_ptr, img_ptr);
}
