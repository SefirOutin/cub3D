/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filled_circle_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:43:03 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 16:05:27 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_circle_pixels(t_img *img, int point, int xx, int color)
{
	put_pixel_to_image(img, xx, MINI_H * 0.5 - point, color);
	put_pixel_to_image(img, xx, MINI_H * 0.5 + point, color);
}

void	filled_circle_draw(t_img *img, int x, int y, int radius)
{
	t_dpoint	current;
	int			m;
	int			xx;

	current.x = 0;
	current.y = 2;
	m = 3 - 4 * radius;
	xx = 0;
	while (current.x <= current.y)
	{
		xx = x - current.y;
		while (xx <= x + current.y)
			put_circle_pixels(img, current.x, xx++, 0xFF0000);
		if (m > 0)
		{
			xx = x - current.x;
			while (xx <= x + current.x)
				put_circle_pixels(img, current.y, xx++, 0xFF0000);
			current.y--;
			m -= 8 * current.y;
		}
		current.x++;
		m += 8 * current.x + 4;
	}
}
