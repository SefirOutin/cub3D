/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/03/30 15:33:33 by soutin           ###   ########.fr       */
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

// Function to calculate the distance between two points
double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to check for collision
bool checkCollision(t_data *data, int futureX, int futureY, int circleRadius) {
    // Calculate the bounding box of the circle at its future position
    int startX = futureX - circleRadius;
    int startY = futureY - circleRadius;
    int endX = futureX + circleRadius;
    int endY = futureY + circleRadius;

    // Ensure the bounding box is within the map
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    // if (endX >= MINI_W) endX = MINI_W - 1;
    // if (endY >= MINI_H) endY = MINI_H - 1;

    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            // Check if the cell is a wall
            if (data->map[y / 15][x / 15] == '1') {
                // Check if the distance from the circle's future center to the cell's center is less than or equal to the circle's radius
                if (distance(futureX, futureY, x, y) <= circleRadius) {
                    return true; // Collision detected
                }
            }
        }
    }

    return false; // No collision detected
}

void	move(t_data *data, double x, double y, double rotation_angle)
{
	if ((x || y) && checkCollision(data, data->player_mini.pos.x + x * 0.3, data->player_mini.pos.y + y * 0.3, 2))
		return ;
	data->player.pos.x += x * 0.02;
	data->player.pos.y += y * 0.02;
	data->player_mini.pos.x += x * 0.3;
	data->player_mini.pos.y += y * 0.3;
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
