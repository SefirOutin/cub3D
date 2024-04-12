/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_data_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:16:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 17:17:30 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_data(t_data *data, int c, int x, int y)
{
	if (c == 'N')
	{
		data->player.direction = 90;
	}
	if (c == 'S')
	{
		data->player.direction = 270;
	}
	if (c == 'W')
	{
		data->player.direction = 180;
	}
	if (c == 'E')
	{
		data->player.direction = 0;
	}
	data->player.pos.x = x + 0.5;
	data->player.pos.y = y + 0.5;
	data->player_mini.pos.x = x * 15 + 7;
	data->player_mini.pos.y = y * 15 + 7;
}

void	find_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NWSE", data->map[y][x]))
			{
				get_player_data(data, data->map[y][x], x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}
