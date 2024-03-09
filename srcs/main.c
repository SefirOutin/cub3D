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

void	move(t_data *data, double x, double y, double rotation_angle)
{
	// int	i = 0;

	// while (i++ < 2000)
	if (check_collision(data, x, y))
		return ;
	erase_floors(data);
	data->player.px += x;
	data->player.py += y;
	data->player.direction = rotation_angle;
	filled_circle_draw(data, 6);
	rotate(data);
	return ;
}

// int	background(t_data *data)
// {
// 	int		x;
// 	int		y;
// 	int		i;
	
// 	y = 0;
// 	if (init_img(data))
// 		return (-1);
// 	while (data->map[y])
// 	{
// 		x = 0;
// 		while (data->map[y][x])
// 		{
// 			i = 0;
// 			while (i < 50)
// 			{
// 				put_pixel_to_image(data->img.img, (x * 50) + i, (y * 50) + i, 0xFFFFFF);
// 				i++;
// 			}
// 			x++;
// 		}
// 		y++;
// 		// if (!(i % data->img.bpp))
// 		// 	data->img.addr[i] = 0xFFFFFF;
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	// mlx_destroy_image(data->mlx_ptr, data->img.img);
// 	// ft_memset(&data->img, 0, sizeof(t_img));
// 	return (0);
// }

int	background(t_data *data)
{
	int		y;
	int		x;

	y = 0;
	if (init_img(data))
		return (-1);
	// printf("ok\n");
	while (y < data->mnmap.y_max * 50)
	{
		x = 0;
		while (x < data->mnmap.x_max * 50)
		{
			put_pixel_to_image(&data->img, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	ft_memset(&data->img, 0, sizeof(t_img));
	return (0);
}

void	first_display(t_data *data)
{
	background(data);
	display_map(data);
	filled_circle_draw(data, 6);
	rotate(data);
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
