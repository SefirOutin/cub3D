/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/14 17:12:33 by soutin           ###   ########.fr       */
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
	ray->end.x = ceil(ray->end.x + len * ray->len_one_u.x);
	ray->end.y = ceil(ray->end.y - len * ray->len_one_u.y);
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

// Fonction pour créer une section entre deux points
// int	create_section(t_data *data, t_point end, int numPoints, t_point **section)
// {
// 	t_point	start;
// 	double	ratio;
// 	int		i;

// 	i = 0;
// 	start.x = data->player.px;
// 	start.y = data->player.py;
// 	*section = (t_point *)ft_calloc(numPoints, sizeof(t_point));
// 	if (!section)
// 		return (1);
// 	while (i < numPoints)
// 	{
// 		ratio = (double)i / (double)(numPoints - 1);
// 		(*section)[i].x = start.x + ratio * (end.x - start.x);
// 		(*section)[i].y = start.y +  ratio * (end.y - start.y);
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
// 			(*section)[i].x, (*section)[i].y, 0x7FFF00);
// 		i++;
// 	}
// 	return (0);
// }

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
		delta.y = ray->end.y - (floor(ray->end.y  * 0.02) * data->mnmap.size) + 1;
	else
		delta.y = (ceil(ray->end.y * 0.02) * data->mnmap.size) - ray->end.y + 1;
	if ((ray->angle_deg > 90 && ray->angle_deg < 270))
		delta.x = ray->end.x - (floor(ray->end.x * 0.02) * data->mnmap.size) + 1;
	else
		delta.x = (ceil(ray->end.x * 0.02) * data->mnmap.size) - ray->end.x + 1;
	// printf("delta unit len x:%f y:%f\n", delta.x, delta.y);
	
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
		if(ray->end.x < data->player.px)
			second.x++;
		else if(ray->end.x > data->player.px)
			second.x--;	
		if (data->map[(int)first.y][(int)first.x] == '1'
		&& data->map[(int)second.y][(int)second.x] == '1')
			return (1);
	}
	return (0);
}

void	find_next_wall(t_data *data, t_ray *ray, double curr_ray)
{
	// t_point	len;
	// int i = 0;
	// int ratio;
	
	ray->angle_deg = fix_ang(data->player.direction + curr_ray - FOV * 0.5);
	ray->angle_rad = deg_to_rad(ray->angle_deg);
	ray->len_one_u.x = cos(ray->angle_rad);
	ray->len_one_u.y = sin(ray->angle_rad);
	ray->end.x = data->player.px;
	ray->end.y = data->player.py;
	ray->hypo_len_one_u.x =  sqrt(1 + pow((ray->len_one_u.y) / (ray->len_one_u.x), 2));
	ray->hypo_len_one_u.y = sqrt(1 + pow((ray->len_one_u.x) / (ray->len_one_u.y), 2));
	// ray->v_camera.x = -sin(ray->angle_rad);
	while ((data->map[(int)(ray->end.y * 0.02)][(int)(ray->end.x * 0.02)] != '1'))
	{
		check_next_edges(data, ray);
		if (check_angles(data, ray))
			return ;
	}
	ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
	// printf("len:%f ray:%f\n", ray->len, curr_ray);
	// double x = ray->len * cos(ray->angle_rad - deg_to_rad(data->player.direction));
	// printf("ray len before %f\n", ray->len);
	// printf("ray len after %f\n", ray->len);
	// len.x = ray->end.x + x;
	// len.y = x + ray->end.y;
	// while (i < 50)
	// {
	// 	ratio = (double)i / (double)(50 - 1);
	// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr,
	// 		len.x + ratio * (ray->end.x - len.x),
	// 		len.y +  ratio * (ray->end.y - len.y), 0x7FFF00);
	// 	// printf("put x:%f y:%f\n", (data->player.px + ray->len_one_u.x) + ratio * ((data->player.px + len.x) + (data->player.px + ray->len_one_u.x)), (data->player.py + ray->len_one_u.y) +  ratio * ((data->player.py - len.y) + (data->player.py + ray->len_one_u.y)));
		
	// 	i++;
	// }
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
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			data->player.px + ratio * (ray->end.x - data->player.px),
			data->player.py +  ratio * (ray->end.y - data->player.py), 0x7FFF00);
		i++;
	}
	
}

int	create_rays(t_data *data)
{
	t_ray	ray;
	int		curr_ray;
	double	angle_ratio;
	
	curr_ray = 0;
	angle_ratio = FOV / 360;
	// printf("ratio :%f\n", angle_ratio);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px, data->player.py, 0x0000FF);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px - 1, data->player.py, 0x0000FF);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px + 1, data->player.py, 0x0000FF);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px, data->player.py - 1, 0x0000FF);
	// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px, data->player.py + 1, 0x0000FF);
	while (curr_ray < 360)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		find_next_wall(data, &ray, curr_ray * 0.25);
		data->rays_len[curr_ray] = ray.len;
		// display_rays(data, &ray);
		curr_ray++;
	}
	return (0);
}
