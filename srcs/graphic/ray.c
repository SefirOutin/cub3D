/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/24 15:45:09 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fix_ang(double a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

double	deg_to_rad(double degrees)
{
	return (degrees * PI / 180.0);
}

// Fonction pour trouver les coordonnées du point sur la section de l'angle
void	find_point_on_section(t_ray *ray, double len)
{
	ray->len += len;
	ray->end.x = ray->end.x + len * ray->len_one_u.x;
	ray->end.y = ray->end.y - len * ray->len_one_u.y;
}

int diff_nearest_50x(int x)
{
    // Calcul du multiple de 50 le plus proche
    int nearestMultiple = 50 * (x / 50);
    // Calcul de la différence
    int difference = x - nearestMultiple;
	
	if (difference > 25)
		return (50 - difference);
    return (difference);
}


int	get_quadrant(int angle)
{
	if (angle >= 0 && angle < 89)
		return (0);
	if (angle >=90  && angle < 180)
		return (1);
	if (angle >= 180 && angle < 270)
		return (2);
	if (angle >= 270 && angle < 360)
		return (3);
	return (-1);
}

void	check_first_cell(t_ray *ray, t_point *step)
{
	t_point	delta;
	
	if (ray->angle_deg < 180)
	{
		step->y = -1;
		delta.y = ray->end.y - (int)ray->end.y;
	}
	else
	{
		step->y = 1;
		delta.y = ceil(ray->end.y) - ray->end.y;
	}
	if ((ray->angle_deg > 90 && ray->angle_deg < 270))
	{
		step->x = -1;
		delta.x = ray->end.x - (int)ray->end.x;
	}
	else
	{
		step->x = 1;
		delta.x = ceil(ray->end.x) - ray->end.x;
	}
	ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
	ray->vlen.y = delta.y * ray->hypo_len_one_u.y;
}

int	check_next_edges(t_data *data, t_ray *ray, int is_first, t_point *step, t_point map)
{
	if (!is_first)
		check_first_cell(ray, step);
	else
	{
		if (ray->vlen.x < ray->vlen.y)
			ray->vlen.x += ray->hypo_len_one_u.x;
		else
			ray->vlen.y += ray->hypo_len_one_u.y;
	}
	if (ray->vlen.x < ray->vlen.y)
	{
		if (data->map[(int)map.y][(int)(map.x + step->x)] == '1')
			find_point_on_section(ray, ray->vlen.x);
		return (0);
	}	
	else
	{
		if (data->map[(int)(map.y + step->y)][(int)map.x] == '1')
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
	ray->hypo_len_one_u.x =  sqrt(1 + pow((ray->len_one_u.y) / (ray->len_one_u.x), 2));
	ray->hypo_len_one_u.y = sqrt(1 + pow((ray->len_one_u.x) / (ray->len_one_u.y), 2));
}

void	find_next_wall(t_data *data, t_ray *ray, double curr_ray)
{
	t_point step;
	t_point	map;
	int	i;
	// int	side;
	
	i = 0;
	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;
	init_ray(data, ray, curr_ray);
	while (1)
	{
		if (!check_next_edges(data, ray, i++, &step, map))
		{
			map.x += step.x;
			// side = 0;
		}
		else
		{
			map.y += step.y;
			// side = 1;
		}
		if (data->map[(int)map.y][(int)map.x] == '1')
			break ;
	}
	ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
}



int	create_rays(t_data *data)
{
	int		curr_ray;
	double	angle_ratio;
	
	curr_ray = 0;
	angle_ratio = (double)FOV / (double)data->main_img.nb_rays;
	data->main_img.rays = ft_calloc(data->main_img.nb_rays, sizeof(t_ray));
	while (curr_ray < data->main_img.nb_rays)
	{
		find_next_wall(data, &data->main_img.rays[curr_ray], curr_ray * angle_ratio);
		curr_ray++;
	}
	return (0);
}
