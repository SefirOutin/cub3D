/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 18:47:31 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

int	can_move(t_data *data, double x, double y, double rotation_angle)
{
	return (1);
}

void	move(t_data *data, double x, double y, double rotation_angle)
{
	if (can_move(data, x, y, rotation_angle))
	{
		data->player.pos.x += x * 0.02;
		data->player.pos.y += y * 0.02;
		data->player_mini.pos.x += x * 0.3;
		data->player_mini.pos.y += y * 0.3;
		data->player.direction = fix_ang(data->player.direction
				+ rotation_angle);
	}
	create_rays(data);
	view(data);
	create_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
		data->main.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main.view.img);
	return ;
}

void	first_display(t_data *data)
{
	create_rays(data);
	view(data);
	create_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
		data->main.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main.view.img);
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
