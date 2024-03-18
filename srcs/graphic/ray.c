/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/18 15:02:37 by soutin           ###   ########.fr       */
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
	ray->len += (int)len;
	ray->end.x = round(ray->end.x + len * ray->len_one_u.x);
	ray->end.y = round(ray->end.y - len * ray->len_one_u.y);
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

int	check_next_edges(t_data *data, t_ray *ray)
{
	t_point	delta;
	
	// calcule la distance du joueur par rapport aux bords de la case que le joueur regarde (sert à vlen)
	if (ray->angle_deg > 0 && ray->angle_deg < 180)
		delta.y = ray->end.y - (floor(ray->end.y  * 0.02) * data->minimap.size) + 1;
	else
		delta.y = (ceil(ray->end.y * 0.02) * data->minimap.size) - ray->end.y + 1;
	if ((ray->angle_deg > 90 && ray->angle_deg < 270))
		delta.x = ray->end.x - (floor(ray->end.x * 0.02) * data->minimap.size) + 1;
	else
		delta.x = (ceil(ray->end.x * 0.02) * data->minimap.size) - ray->end.x + 1;
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
	ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
	ray->vlen.y = delta.y * ray->hypo_len_one_u.y;
	// printf("vlen x:%f Y:%f\n", ray->vlen.x, ray->vlen.y);
	if ((ray->vlen.x < ray->vlen.y))
		return (find_point_on_section(ray, ray->vlen.x), (int)ray->vlen.x);
	else
		return (find_point_on_section(ray, ray->vlen.y), (int)ray->vlen.y);
}

int	check_angles(t_data *data, t_ray *ray)
{
	t_point	first;
	t_point	second;
	
	first.x = (int)(ray->end.x * 0.02);
	first.y = (int)(ray->end.y * 0.02);
	second.x = (int)(ray->end.x * 0.02);
	second.y = (int)(ray->end.y * 0.02);
	if((abs(diff_nearest_50x(ray->end.x) * diff_nearest_50x(ray->end.y)) < 2))
	{
		if (ray->angle_deg > 180)
			first.y--;
		else
			first.y++;
		if(ray->end.x < data->player.pos.x)
			second.x++;
		else if(ray->end.x > data->player.pos.x)
			second.x--;	
		if (data->map[(int)first.y][(int)first.x] == '1'
		&& data->map[(int)second.y][(int)second.x] == '1')
			return (1);
	}
	return (0);
}

void	find_next_wall(t_data *data, t_ray *ray, double curr_ray)
{
	ray->angle_deg = fix_ang(data->player.direction - FOV * 0.5 + curr_ray );
	ray->angle_rad = deg_to_rad(ray->angle_deg);
	ray->len_one_u.x = cos(ray->angle_rad);
	ray->len_one_u.y = sin(ray->angle_rad);
	ray->end.x = data->player.pos.x;
	ray->end.y = data->player.pos.y;
	ray->hypo_len_one_u.x =  sqrt(1 + pow((ray->len_one_u.y) / (ray->len_one_u.x), 2));
	ray->hypo_len_one_u.y = sqrt(1 + pow((ray->len_one_u.x) / (ray->len_one_u.y), 2));
	while ((data->map[(int)(ray->end.y * 0.02)][(int)(ray->end.x * 0.02)] != '1'))
	{
		check_next_edges(data, ray);
		if (check_angles(data, ray))
			return ;
	}
	ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
}

void	display_rays(t_data *data, t_ray *ray)
{
	int		i;
	double	ratio;
	int		num_points;
	
	i = 0;
	num_points = ray->len * 0.2;
	while (i  < num_points)
	{
		ratio = (double)i / (double)(num_points - 1);
		mlx_pixel_put(data->win.mlx_ptr, data->win.win_ptr,
			data->player.pos.x + ratio * (ray->end.x - data->player.pos.x),
			data->player.pos.y +  ratio * (ray->end.y - data->player.pos.y), 0x7FFF00);
		i++;
	}
	
}

int	create_rays(t_data *data)
{
	t_ray	ray;
	int		curr_ray;
	double	angle_ratio;
	
	curr_ray = 0;
	angle_ratio = 0.28125;
	while (curr_ray < data->main_img.nb_rays)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		find_next_wall(data, &ray, curr_ray * angle_ratio);
		data->main_img.rays_len[curr_ray] = ray.len;
		// display_rays(data, &ray);
		curr_ray++;
	}
	return (0);
}
