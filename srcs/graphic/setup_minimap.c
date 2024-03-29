/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:26:33 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 18:43:53 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_minimap_window(t_img *win_minimap, t_data *data);
void	print_minimap(t_img *win_minimap, t_data *data, t_img *asset);

void	create_minimap(t_data *data)
{
	t_img	window_minimap;

	if (init_img(data, &window_minimap, MINI_W, MINI_H))
		return ;
	print_minimap(&window_minimap, data, data->minimap.asset);
	filled_circle_draw(&window_minimap, MINI_W * 0.5, MINI_H * 0.5, 2);
	put_img_to_img(&data->main.view, window_minimap, 10, 10);
	destroy_image(window_minimap, data);
}

void	create_minimap_window(t_img *win_minimap, t_data *data)
{
	win_minimap->img = mlx_new_image(data->win.mlx_ptr, MINI_W, MINI_H);
	win_minimap->addr = (int *)mlx_get_data_addr(win_minimap->img,
			&(win_minimap->bpp), &(win_minimap->line_l),
			&(win_minimap->endian));
}

void	print_minimap(t_img *win_minimap, t_data *data, t_img *asset)
{
	int			i;
	int			j;
	int			player_x;
	int			player_y;
	t_ipoint	point;

	player_x = data->player.pos.x * 15;
	player_y = data->player.pos.y * 15;
	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			point.x = (i * 15) - (player_x - MINI_H / 2);
			point.y = (j * 15) - (player_y - MINI_W / 2);
			if (ft_strchr("1", data->map[j][i]))
				put_img_to_mini_img(win_minimap, asset[0], point, 15);
			if (ft_strchr("0NSWE", data->map[j][i]))
				put_img_to_mini_img(win_minimap, asset[1], point, 15);
			i++;
		}
		j++;
	}
}

