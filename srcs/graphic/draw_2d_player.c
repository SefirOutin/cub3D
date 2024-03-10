/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:28:45 by soutin            #+#    #+#             */
/*   Updated: 2024/03/10 13:25:11 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	filled_circle_draw(t_data *data, int radius)
{
	t_point	current;
	t_img	img;
	int		m;
	int		xx;

	img = init_img(data, 50, 50);
	current.x = 0;
	current.y = radius;
	m = 3 - 4 * radius;
	xx = 0;
	while (current.x <= current.y)
	{
		xx = data->player.px - current.y;
		while (xx <= data->player.px + current.y)
			put_circle_pixels(data, &img, current.x, xx++, 0x00FFFFFF);
		if (m > 0)
		{
			xx = data->player.px - current.x;
			while (xx <= data->player.px + current.x)
				put_circle_pixels(data, &img, current.y, xx++, 0x00FFFFFF);
			current.y--;
			m -= 8 * current.y;
		}
		current.x++;
		m += 8 * current.x + 4;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.img, data->player.px, data->player.py);
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
