/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:46:00 by soutin            #+#    #+#             */
/*   Updated: 2024/03/30 16:06:00 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool checkCollision(t_data *data, int futureX, int futureY)
{
    t_ipoint	start;
	t_ipoint	end;
	int			curr_y;
	
	start.x = futureX - 3;
    start.y = futureY - 3;
    end.x = futureX + 3;
    end.y = futureY + 3;
    while (start.x <= end.x)
	{
		curr_y = start.y;
		while (curr_y < end.y)
		{
            if (data->map[curr_y / 15][start.x / 15] == '1')
                if (distance(futureX, futureY, start.x, curr_y) <= 3)
                    return true;
			curr_y++;
		}
		start.x++;
	}
    return false;
}

void	move(t_data *data, double x, double y, double rotation_angle)
{
	if ((x || y) && !checkCollision(data, data->player_mini.pos.x + x * 0.3,
		data->player_mini.pos.y + y * 0.3))
	{
		data->player.pos.x += x * 0.02;
		data->player.pos.y += y * 0.02;
		data->player_mini.pos.x += x * 0.3;
		data->player_mini.pos.y += y * 0.3;
	}
	data->player.direction = fix_ang(data->player.direction
			+ rotation_angle);
	create_rays(data);
	view(data);
	create_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
		data->main.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main.view.img);
	return ;
}
