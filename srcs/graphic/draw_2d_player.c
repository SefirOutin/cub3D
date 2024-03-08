/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:28:45 by soutin            #+#    #+#             */
/*   Updated: 2024/03/08 17:48:49 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	filled_circle_draw(t_data *data, int radius)
{
	t_point	current;
	int		m;
	int		xx;

	current.x = 0;
	current.y = radius;
	m = 3 - 4 * radius;
	xx = 0;
	while (current.x <= current.y)
	{
		xx = data->player.px - current.y;
		while (xx <= data->player.px + current.y)
			put_circle_pixels(data, current.x, xx++, 0xFF0000);
		if (m > 0)
		{
			xx = data->player.px - current.x;
			while (xx <= data->player.px + current.x)
				put_circle_pixels(data, current.y, xx++, 0xFF0000);
			current.y--;
			m -= 8 * current.y;
		}
		current.x++;
		m += 8 * current.x + 4;
	}
}

void	filled_circle_erase(t_data *data, int radius)
{
	t_point	current;
	int		m;
	int		xx;

	current.x = 0;
	current.y = radius;
	m = 3 - 4 * radius;
	xx = 0;
	while (current.x <= current.y)
	{
		xx = data->player.px - current.y;
		while (xx <= data->player.px + current.y)
			put_circle_pixels(data, current.x, xx++, 0xFFFFFF);
		if (m > 0)
		{
			xx = data->player.px - current.x;
			while (xx <= data->player.px + current.x)
				put_circle_pixels(data, current.y, xx++, 0xFFFFFF);
			current.y--;
			m -= 8 * current.y;
		}
		current.x++;
		m += 8 * current.x + 4;
	}
}
