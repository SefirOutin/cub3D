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
	if (data->map[(int)((data->player.py + y) / 50)][(int)((data->player.px + x
				+ 6) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 6) / 50)][(int)((data->player.px
				+ x) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y - 6) / 50)][(int)((data->player.px
				+ x - 6) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 6) / 50)][(int)((data->player.px
				+ x) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y - 3) / 50)][(int)((data->player.px
				+ x - 3) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 3) / 50)][(int)((data->player.px
				+ x - 3) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y - 3) / 50)][(int)((data->player.px
				+ x + 3) / 50)] == '1')
		return (1);
	if (data->map[(int)((data->player.py + y + 3) / 50)][(int)((data->player.px
				+ x + 3) / 50)] == '1')
		return (1);
	return (0);
}

void	move(t_data *data, double x, double y, double angle_degrees)
{
	int	i;

	i = 0;
	if (check_collision(data, x, y))
		return ;
	// erased_ray(data);
	while (i < 90)
		erase_direction(data, angle_degrees + i++, 90);
	mid_point_circle_erase(data, 15);
	filled_circle_erase(data, 6);
	data->player.px += x;
	data->player.py += y;
	rotate(data, angle_degrees);
	// put_ray(data);
	filled_circle_draw(data, 6);
	mid_point_circle_draw(data, 15);
	return ;
}

t_img	init_mlx_img(t_data *data)
{
	t_img	new_img;
	int	i;
	
	i = 0;
	new_img.img = mlx_new_image(data->mlx_ptr, data->img.size_x,
			data->img.size_y);
	if (!new_img.img)
		return (new_img);
	new_img.addr = (int *)mlx_get_data_addr(new_img.img, &new_img.bpp,
			&new_img.line_l, &new_img.endian);
	while (new_img.addr[i])
		new_img.addr[i++] = 0xFFFFFF;
	return (new_img);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argv[1]))
		return (1);
	data.player.direction = 0;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.img.x_max * 50,
			(data.img.y_max) * 50, "MazeCub3D");
	if (!data.win_ptr)
		return (free(data.win_ptr), -1);
	init_img(&data);
	data.img.size_x = 50;
	data.img.size_y = 50;
	display_map(&data);
	filled_circle_draw(&data, 6);
	mid_point_circle_draw(&data, 15);
	// dislay_player(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, release_inputs, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, get_inputs, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
			&data);
	mlx_loop_hook(data.mlx_ptr, on_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
