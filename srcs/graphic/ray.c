/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/21 18:13:08by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double degrees)
{
	return (degrees * PI / 180.0);
}

double	fix_ang(double a)
{
	while (a > 359)
		a -= 360;
	while (a < 0)
		a += 360;
	return (a);
}

int	create_rays(t_data *data)
{
	t_point pos;
	t_point dir;
	t_point plane;
	t_point camera;
	t_point ray_dir;
	t_point map;
	t_point side_dist;
	t_point delta_dist;
	t_point step;
	int hit;
	int side;
	double perp_wall_dist;
	double angle;
	double fov_ratio;
	int x;

	x = 0;
	angle = deg_to_rad(data->player.direction);
	fov_ratio = tan(angle / 2);
	pos = data->player.pos;
	dir.x = cos(angle);
	dir.y = sin(angle);
	plane.x = dir.x * fov_ratio;
	plane.y = -dir.y * fov_ratio;
	printf("plane x %f plane y %f",plane.x,plane.y);
	while (x++ < data->win.w)
	{
		camera.x = 2 * x / (double)data->win.w - 1;
		ray_dir.x = dir.x + plane.x * camera.x;
		ray_dir.y = dir.y + plane.y * camera.x;
		map.x = (int)pos.x;
		map.y = (int)pos.y;
		if (ray_dir.x == 0)
			delta_dist.x = 1e30;
		else
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = fabs(1 / ray_dir.y);
		hit = 0;
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			// Check if ray has hit a wall
			if (data->map[(int)map.y][(int)map.x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist.x - delta_dist.x);
		else
			perp_wall_dist = (side_dist.y - delta_dist.y);
		data->main_img.rays_len[x - 1] = perp_wall_dist;
	}

	return (0);
}