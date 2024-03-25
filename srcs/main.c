/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/28 00:40:35by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

int	check_collision(t_data *data, double x, double y)
{
	if (data->map[(int)((data->player.pos.y + y))][(int)((data->player.pos.x + x
				+ 6))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 6))][(int)((data->player.pos.x
				+ x))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 6))][(int)((data->player.pos.x
				+ x - 6))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 6))][(int)((data->player.pos.x
				+ x))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 3))][(int)((data->player.pos.x
				+ x - 3))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 3))][(int)((data->player.pos.x
				+ x - 3))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 3))][(int)((data->player.pos.x
				+ x + 3))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 3))][(int)((data->player.pos.x
				+ x + 3))] == '1')
		return (1);
	return (0);
}

t_point	cool_rotate(t_point pixel, double angle)
{
	t_point	new;

	new.x = round((pixel.x - 0.5) * cos(angle) + (pixel.y - 0.5) * sin(angle));
	new.y = round((pixel.x - 0.5) * sin(angle) + (pixel.y - 0.5) * cos(angle));
	return (new);
}
int	can_move(t_data *data, double x, double y, double rotation_angle)
{
	if (data->map[+(int)floor(data->player.pos.y + y 
			* 0.01)][(int)floor(data->player.pos.x + x * 0.01)] == '1')
		return (0);
	else
		return (1);
}
void	move(t_data *data, double x, double y, double rotation_angle)
{
	if (can_move(data, x, y, rotation_angle))
	{
		data->player.pos.x += x * 0.01;
		data->player.pos.y += y * 0.01;
		data->player_mini.pos.x += x * 0.3;
		data->player_mini.pos.y += y * 0.3;
		data->player.direction = fix_ang(data->player.direction
				+ rotation_angle);
	}
	create_rays(data);
	view(data);
	setup_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
		data->main_img.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main_img.view.img);
	return ;
}

void	first_display(t_data *data)
{
	create_rays(data);
	view(data);
	setup_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
		data->main_img.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main_img.view.img);
}
int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argv[1]))
		return (1);
	if (init_mlx_data(&data))
		return (exit_and_free(&data), 1);
	first_display(&data);
	init_hook_and_loop(&data);
	return (0);
}
