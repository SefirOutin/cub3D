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
void	init_value(t_data *data, t_raycaster *p)
{
	p->dir.x = (deg_to_rad(data->player.direction));
	p->dir.y = -(deg_to_rad(data->player.direction));
	p->pos.x = data->player.pos.x;
	p->pos.y = data->player.pos.y;
	p->plane.x = p->dir.x * tan(deg_to_rad(FOV)/2);
	p->plane.y = p->dir.y * tan(deg_to_rad(FOV)/2);
}
void get_len(t_data *data,t_raycaster *p)
{
	int x_strip;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;

	x_strip = 0;
	while(x_strip < data->win.w)
	{
		camera_x = 2 * x_strip / data->win.w - 1;
		ray_dir_x = p->dir.x + p->plane.x * camera_x;
		ray_dir_y = p->dir.y + p->plane.y * camera_x;

		x_strip++;
	}
}

int	create_rays(t_data *data)
{
	t_raycaster	p;

	init_value(data, &p);
	get_len(data,&p);
	return (0);
}
