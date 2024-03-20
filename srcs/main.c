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
			)][(int)((data->player.pos.x + x + 6))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 6)
			)][(int)((data->player.pos.x + x))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 6)
			)][(int)((data->player.pos.x + x - 6))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 6)
		)][(int)((data->player.pos.x + x) )] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 3)
			)][(int)((data->player.pos.x + x - 3) )] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 3)
			)][(int)((data->player.pos.x + x - 3))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y - 3)
			)][(int)((data->player.pos.x + x + 3))] == '1')
		return (1);
	if (data->map[(int)((data->player.pos.y + y + 3)
			)][(int)((data->player.pos.x + x + 3) )] == '1')
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
	// if ((x || y) && check_collision(data, x, y))
	// 	return ;
	// erase_floors(data);
	// display_map(data);
	// printf("new x:%f y:%f\n\n", x, y);
	data->player.pos.x += x * 0.02;
	data->player.pos.y += y * 0.02;
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
// fxpoint fixed_cos(t_data *data, fxpoint angle)
// {
// 	int	i;
// 	double	step_size;

// 	step_size = 0.28125;
//     // Calculate the index in the lookup table
//     i = angle / (SHIFT_MASK * step_size);
// 	printf("angle :%f cos %f index :%d\n", fixed_to_double(angle), fixed_to_double(data->cos_table[i]), i);
//     // Lookup the value in the cosine table
//     return data->cos_table[i];
// }

void	first_display(t_data *data)
{
	// background(data);
	// display_map(data);
	// draw_xpm(data, deg_to_rad(fix_ang(data->player.direction - 90)));
	// printf("%f %f\n", fixed_to_double(deg_to_rad(90 << 16)), 90 * PI / 180);
	// printf("cos fx :%u cos m:%u\n", fixed_cos(data, 90 << 16), double_to_fixed(cos(deg_to_rad(90))));
	create_rays(data);
	view(data);
	setup_minimap(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr, data->main_img.view.img, 0, 0);
	mlx_destroy_image(data->win.mlx_ptr, data->main_img.view.img);
	// init_img(data);
	// mid_point_circle_draw(data, 8);
}


// fxpoint fixed_sin(t_data *data, fxpoint angle)
// {
// 	int	i;
// 	double	step_size;

// 	step_size = 0.28125;
//     // Normalize the angle to [0, 360) degrees
//     while (angle < 0)
// 		angle += SHIFT_MASK * data->array_size;
//     angle %= SHIFT_MASK * data->array_size;

//     // Calculate the index in the lookup table
//     i = angle / (SHIFT_MASK * step_size);

//     // Lookup the value in the cosine table
//     return data->sin_table[i];
// }

// void	create_table(t_data *data)
// {
// 	int	i;
// 	double	var;

// 	data->array_size = (double)(360 / 0.28125);
//     data->cos_table = ft_calloc(data->array_size, sizeof(fxpoint));
//     data->sin_table = ft_calloc(data->array_size, sizeof(fxpoint));
// 	var = PI / 180;
// 	i = 0;
// 	while (i < data->array_size)
// 	{
//         double angle = i * 0.28125 * var;
//         data->cos_table[i] = double_to_fixed(cos(angle));
// 		if (i == 320)
// 			printf("cos %u angle:%f\n", data->cos_table[i], i * 0.28125);
//         data->sin_table[i] = double_to_fixed(sin(angle));
// 		i++;
// 	}
// 	// i = 0;
// 	// while (i < data->array_size)
// 	// {
// 	// 	// printf("cos :%u x:%d\n", data->cos_table[i] >> SHIFT_AMOUNT, i);
// 	// 	i++;
// 	// }
// }

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argv[1]))
		return (1);
	if (init_mlx_data(&data))
		return (exit_and_free(&data), 1);
	// create_table(&data);
	first_display(&data);
	init_hook_and_loop(&data);
	return (0);
}


