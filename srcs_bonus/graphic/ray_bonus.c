/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 15:01:08 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_point_on_section(t_ray *ray, double len);
void	check_first_cell(t_ray *ray);
int		check_next_edges(t_data *data, t_ray *ray, int is_first, t_dpoint map);
void	find_next_wall(t_data *data, t_ray *ray, double curr_ray);

int	create_rays(t_data *data)
{
	int		curr_ray;
	double	angle_ratio;

	curr_ray = 0;
	angle_ratio = (double)FOV / (double)data->main.nb_rays;
	data->main.rays = ft_calloc(data->main.nb_rays, sizeof(t_ray));
	while (curr_ray < data->main.nb_rays)
	{
		find_next_wall(data, &data->main.rays[curr_ray], curr_ray
			* angle_ratio);
		curr_ray++;
	}
	return (0);
}

void	check_first_cell(t_ray *ray)
{
	t_dpoint	delta;

	if (ray->angle_deg < 180)
	{
		ray->step.y = -1;
		delta.y = ray->end.y - (int)ray->end.y;
	}
	else
	{
		ray->step.y = 1;
		delta.y = ceil(ray->end.y) - ray->end.y;
	}
	if ((ray->angle_deg > 90 && ray->angle_deg < 270))
	{
		ray->step.x = -1;
		delta.x = ray->end.x - (int)ray->end.x;
	}
	else
	{
		ray->step.x = 1;
		delta.x = ceil(ray->end.x) - ray->end.x;
	}
	ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
	ray->vlen.y = delta.y * ray->hypo_len_one_u.y;
}

int	check_next_edges(t_data *data, t_ray *ray, int is_first, t_dpoint map)
{
	if (!is_first)
		check_first_cell(ray);
	else
	{
		if (ray->vlen.x < ray->vlen.y)
			ray->vlen.x += ray->hypo_len_one_u.x;
		else
			ray->vlen.y += ray->hypo_len_one_u.y;
	}
	if (ray->vlen.x < ray->vlen.y)
	{
		if (data->map[(int)map.y][(int)(map.x + ray->step.x)] == '1')
			find_point_on_section(ray, ray->vlen.x);
		return (0);
	}
	else
	{
		if (data->map[(int)(map.y + ray->step.y)][(int)map.x] == '1')
			find_point_on_section(ray, ray->vlen.y);
		return (1);
	}
}

void	init_ray(t_data *data, t_ray *ray, double curr_ray)
{
	ray->angle_deg = fix_ang(data->player.direction + curr_ray - FOV * 0.5);
	ray->angle_rad = deg_to_rad(ray->angle_deg);
	ray->len_one_u.x = cos(ray->angle_rad);
	ray->len_one_u.y = sin(ray->angle_rad);
	ray->end.x = data->player.pos.x;
	ray->end.y = data->player.pos.y;
	ray->hypo_len_one_u.x = sqrt(1 + pow((ray->len_one_u.y)
				/ (ray->len_one_u.x), 2));
	ray->hypo_len_one_u.y = sqrt(1 + pow((ray->len_one_u.x)
				/ (ray->len_one_u.y), 2));
}

void	find_next_wall(t_data *data, t_ray *ray, double curr_ray)
{
	t_dpoint	map;
	int			i;

	i = 0;
	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;
	init_ray(data, ray, curr_ray);
	while (1)
	{
		if (!check_next_edges(data, ray, i++, map))
		{
			map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			map.y += ray->step.y;
			ray->side = 1;
		}
		if (data->map[(int)map.y][(int)map.x] == '1')
			break ;
	}
	ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
}
