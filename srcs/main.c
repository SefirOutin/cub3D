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
	if (data->map[(int)((data->player.pos.y + y)
			/ 50)][(int)((data->player.pos.x + x + 6) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 6)
			/ 50)][(int)((data->player.pos.x + x) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 6)
			/ 50)][(int)((data->player.pos.x + x - 6) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 6)
			/ 50)][(int)((data->player.pos.x + x) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 3)
			/ 50)][(int)((data->player.pos.x + x - 3) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 3)
			/ 50)][(int)((data->player.pos.x + x - 3) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 3)
			/ 50)][(int)((data->player.pos.x + x + 3) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 3)
			/ 50)][(int)((data->player.pos.x + x + 3) / 50)] == '1')
		return (1);
	return (0);
}

t_point	cool_rotate(t_point pixel, double angle)
{
	t_point	new;

	new.x = round((pixel.x - 25) * cos(angle) + (pixel.y - 25) * sin(angle));
	new.y = round((pixel.x - 25) * sin(angle) + (pixel.y - 25) * cos(angle));
	return (new);
}

void	move(t_data *data, double x, double y, double rotation_angle)
{
	if ((x || y) && check_collision(data, x, y))
		return ;
	// erase_floors(data);
	// display_map(data);
	// printf("new x:%f y:%f\n\n", x, y);
	data->player.pos.x += x;
	data->player.pos.y += y;
	data->player_mini.pos.x += x*0.3;
	data->player_mini.pos.y += y*0.3;
	data->player.direction = fix_ang(data->player.direction + rotation_angle);
	// filled_circle_draw(data, 6);
	create_rays(data);
	view(data);
	// draw_xpm(data, deg_to_rad(fix_ang(data->player.direction - 90)));
	setup_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,data->main_img.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main_img.view.img);
	return ;
}

void	first_display(t_data *data)
{
	// background(data);
	// display_map(data);
	// draw_xpm(data, deg_to_rad(fix_ang(data->player.direction - 90)));
	create_rays(data);
	view(data);
	setup_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr, data->main_img.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main_img.view.img);
	// init_img(data);
	// mid_point_circle_draw(data, 8);
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


