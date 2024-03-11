/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:28:45 by soutin            #+#    #+#             */
/*   Updated: 2024/03/11 17:14:32 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



// void	filled_circle_draw(t_data *data, int radius)
// {
// 	t_point	current;
// 	t_img	img;
// 	int		m;
// 	int		xx;

// 	// img = init_img(data, 50, 50);
// 	// background_img(&img, 50, 0xFFFFFF00);
// 	current.x = 0;
// 	current.y = radius;
// 	m = 2 - 3 * radius;
// 	xx = 0;
// 	while (current.x <= current.y)
// 	{
// 		xx = 25 - current.y;
// 		while (xx <= 25 + current.y)
// 			put_circle_pixels(radius, &img, current.x, xx++, 0xFF0000);
// 		if (m > 0)
// 		{
// 			xx = 25 - current.x;
// 			while (xx <= 25 + current.x)
// 				put_circle_pixels(radius, &img, current.y, xx++, 0xFF0000);
// 			current.y--;
// 			m -= 8 * current.y;
// 		}
// 		current.x++;
// 		m += 8 * current.x + 4;
// 	}
// 	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.img, data->player.px - 25, data->player.py - 25);
// }

// void    draw_player(void *img_ptr, void *mlx_ptr, void *win_ptr, int x_pos,
//         int y_pos, double angle)
// {
//     int        color;
//     int        *data;
//     double    angle_rad;
//     int        new_x;
//     int        new_y;

//     int x, y;
//     int bpp, size_line, endian;
//     data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
//     angle_rad = angle * M_PI / 180.0;
//     for (y = 0; y < 50; y++)
//     {
//         for (x = 0; x < 50; x++)
//         {
//             new_x = x_pos + round((x - 25) * cos(angle_rad) - (y - 25) * sin(angle_rad))
//                 + 25;
//             new_y = y_pos - round((x - 25) * sin(angle_rad) + (y - 25) * cos(angle_rad))
//                 + 25;
//             color = data[y * 50 + x];
//             if (color >= 0 && new_x >= 0 && new_x < 1920 && new_y >= 0
//                 && new_y < 1080)
//                 mlx_pixel_put(mlx_ptr, win_ptr, new_x, new_y, color);
//         }
//     }
//     mlx_destroy_image(mlx_ptr, img_ptr);
// }

void draw_xpm(void *img_ptr, void *mlx_ptr, void *win_ptr, int x_pos, int y_pos, double angle)
{
    int color;
    int *data;

    int x, y;
    int bpp, size_line, endian;
    data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
    printf("angle %f\n", angle);
    // Convert the angle to radians
    double angle_rad = fix_ang(angle - 90) * M_PI / 180.0;

    for (y = 0; y < 50; y++)
    {
        for (x = 0; x < 50; x++)
        {
            // Calculate rotated coordinates
            int new_x = round((x - 25) * cos(angle_rad) + (y - 25) * sin(angle_rad)) + x_pos;
            int new_y = round((x - 25) * sin(angle_rad) + (y - 25) * cos(angle_rad)) + y_pos;

            color = data[y * 50 + x];
            if (color >= 0 && new_x >= 0 && new_x < 1920 && new_y >= 0 && new_y < 1080)
                mlx_pixel_put(mlx_ptr, win_ptr, new_x, new_y, color);
        }
    }

    // mlx_destroy_image(mlx_ptr, img_ptr);
}

// void	filled_circle_erase(t_data *data, int radius)
// {
// 	t_point	current;
// 	int		m;
// 	int		xx;

// 	current.x = 0;
// 	current.y = radius;
// 	m = 3 - 4 * radius;
// 	xx = 0;
// 	while (current.x <= current.y)
// 	{
// 		xx = data->player.px - current.y;
// 		while (xx <= data->player.px + current.y)
// 			put_circle_pixels(data, current.x, xx++, 0xFFFFFF);
// 		if (m > 0)
// 		{
// 			xx = data->player.px - current.x;
// 			while (xx <= data->player.px + current.x)
// 				put_circle_pixels(data, current.y, xx++, 0xFFFFFF);
// 			current.y--;
// 			m -= 8 * current.y;
// 		}
// 		current.x++;
// 		m += 8 * current.x + 4;
// 	}
// }
