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

double	fix_ang(double a)
{
	while (a > 359)
		a -= 360;
	while (a < 0)
		a += 360;
	return (a);
}
double	deg_to_rad(double degrees)
{
	return (degrees * PI / 180.0);
}

int	create_rays(t_data *data)
{
	t_point	pos;
	t_point	dir;
	t_point	plane;
	t_point	camera;
	t_point	ray_dir;
	t_point	map;
	t_point	side_dist;
	t_point	delta_dist;
	t_point	step;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		x;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	t_point	draw;
	int		len;

	x = 0;
	pos = data->player.pos;
	dir.x = 0;
	dir.y = -1;
	plane.x = 0.66 * dir.y;
	plane.y = 0.66 * (-1 * dir.x);
	while (x++ < data->win.w)
	{
		camera.x = 2 * x / (double)data->win.w - 1;
		ray_dir.x = dir.x + plane.x * camera.x;
		ray_dir.y = dir.y + plane.y * camera.x;
		map.x = (int)pos.x;
		map.y = (int)pos.y;
		if (ray_dir.x == 0)
			delta_dist.x = fabs(1e30);
		else
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = fabs(1e30);
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
			if (data->map[(int)map.y][(int)map.x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map.x - pos.x + (1 - step.x) / 2) / ray_dir.x;
		else
			perp_wall_dist = (map.y - pos.y + (1 - step.y) / 2) / ray_dir.y;
		lineHeight = (int)(data->win.h / perp_wall_dist);
		drawStart = -lineHeight / 2 + data->win.h / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + data->win.h / 2;
		if (drawEnd >= data->win.h)
			drawEnd = data->win.h - 1;
		draw.x = x;
		draw.y = drawStart;
		len = drawEnd - drawStart;
		if (init_img(data, &data->main_img.view, data->win.w, data->win.h))
			return (-1);
		printf("start %d  end %d\n",drawStart,drawEnd);
		verline(&data->main_img.view,x,drawStart,drawEnd,0x0000FF);
	}
	return (0);
}
