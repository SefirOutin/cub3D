/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:28:45 by soutin            #+#    #+#             */
/*   Updated: 2024/03/02 20:17:31 by soutin           ###   ########.fr       */
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
	// printf("circle player x:%f y:%f\n", data->player.px, data->player.py);
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

void	mid_point_circle_draw(t_data *data, int r)
{
	t_point	current;
	int		P;

	current.x = r;
	current.y = 0;
	P = 1 - r;
	while (current.x > current.y)
	{
		current.y++;
		if (P <= 0)
			P = P + 2 * current.y + 1;
		else
		{
			current.x--;
			P = P + 2 * current.y - 2 * current.x + 1;
		}
		if (!(current.x < current.y))
			mid_point_put_pixels(data, current, 0xFF0000);
	}
}

void	mid_point_circle_erase(t_data *data, int r)
{
	t_point current;
	int P;

	current.x = r;
	current.y = 0;
	P = 1 - r;
	// Initialising the value of P
	while (current.x > current.y)
	{
		current.y++;
		// Mid-point is inside or on the perimeter
		if (P <= 0)
			P = P + 2 * current.y + 1;
		// Mid-point is outside the perimeter
		else
		{
			current.x--;
			P = P + 2 * current.y - 2 * current.x + 1;
		}
		// All the perimeter points have already been printed
		if (!(current.x < current.y))
			mid_point_put_pixels(data, current, 0xFFFFFF);
		// if (current.x < current.y)
		// 	break ;
		// // Printing the generated point and its reflection
		// // in the other octants after translation
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.x + data->player.px, current.y + data->player.py,
		// 	0xFFFFFF);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.x + data->player.px, current.y + data->player.py,
		// 	0xFFFFFF);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.x + data->player.px, -current.y + data->player.py,
		// 	0xFFFFFF);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.x + data->player.px, -current.y
		// 	+ data->player.py, 0xFFFFFF);
		// // If the generated point is on the line x = y then
		// // the perimeter points have already been printed
		// if (current.x != current.y)
		// {
		// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.y + data->player.px, current.x
		// 		+ data->player.py, 0xFFFFFF);
		// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, current.y + data->player.px, -current.x
		// 		+ data->player.py, 0xFFFFFF);
		// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.y + data->player.px, current.x
		// 		+ data->player.py, 0xFFFFFF);
		// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, -current.y + data->player.px, -current.x
		// 		+ data->player.py, 0xFFFFFF);
		// }
	}
}