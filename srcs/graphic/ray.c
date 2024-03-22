/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/22 19:37:50 by soutin           ###   ########.fr       */
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

int	check_angles(t_data *data, t_ray *ray)
{
	t_point	first;
	t_point	second;
	
	first.x = (int)ray->end.x;
	first.y = (int)ray->end.y;
	second.x = (int)ray->end.x;
	second.y = (int)ray->end.y;
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

void	first_cell(t_ray *ray, t_point *step, double curr_ray)
{
	t_point	delta;
	
	if (ray->angle_rad < PI)
	{
		step->y = -1;
		delta.y = ray->end.y - (int)ray->end.y;
	}
	else
	{
		step->y = 1;
		delta.y = ceil(ray->end.y) - ray->end.y;
	}
	if ((ray->angle_rad > PI * 0.5 && 3 * PI * 0.5))
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
	if (curr_ray == 45)
		printf("delta X:%f y:%f\n", delta.x, delta.y);
}

int	check_next_edges(t_data *data, t_ray *ray, int is_first, t_point *step, t_point map, double curr_ray)
{
	// calcule la distance du joueur par rapport aux bords de la case que le joueur regarde (sert à vlen)
	if (!is_first)
		first_cell(ray, step, curr_ray);
	else
	{
		if (ray->vlen.x < ray->vlen.y)
			ray->vlen.x += ray->hypo_len_one_u.x;
		else
			ray->vlen.y += ray->hypo_len_one_u.y;
	}
	if ((ray->vlen.x < ray->vlen.y) && data->map[(int)map.y][(int)(map.x + step->x)] == '1')
	{
		return (find_point_on_section(ray, ray->vlen.x), 0);
	}	
	else if (data->map[(int)(map.y + step->y)][(int)map.x] == '1')
	{
		return (find_point_on_section(ray, ray->vlen.y), 1);
	}
	if ((ray->vlen.x < ray->vlen.y))
		return (0);
	else
		return (1);
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
}

void	find_next_wall(t_data *data, t_ray *ray, double curr_ray)
{
	// t_point	delta;
	t_point step;
	t_point	map;
	int	i;
	int	side;
	
	i = 0;
	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;
	ray->angle_deg = fix_ang(data->player.direction + curr_ray - FOV * 0.5);
	ray->angle_rad = deg_to_rad(ray->angle_deg);
	ray->len_one_u.x = cos(ray->angle_rad);
	ray->len_one_u.y = sin(ray->angle_rad);
	ray->end.x = data->player.pos.x;
	ray->end.y = data->player.pos.y;
	ray->hypo_len_one_u.x =  sqrt(1 + pow((ray->len_one_u.y) / (ray->len_one_u.x), 2));
	ray->hypo_len_one_u.y = sqrt(1 + pow((ray->len_one_u.x) / (ray->len_one_u.y), 2));
	while (1)
	{
		if (curr_ray == 45)
			printf("end x:%f y:%f\n", ray->end.x, ray->end.y);	
		if (!check_next_edges(data, ray, i++, &step, map, curr_ray))
		{
			map.x += step.x;
			side = 0;
		}
		else
		{
			map.y += step.y;
			side = 1;
		}
		if (data->map[(int)map.y][(int)map.x] == '1')
		{
			if (curr_ray == 45)
			{
				printf("end x:%f y:%f\n", ray->end.x, ray->end.y);
				printf("map x:%f y:%f char :%c\n", map.x, map.y, data->map[(int)map.y][(int)map.x]);		
				printf("ray len :%f\n", ray->len);
			}
			break ;
		}
		// if (check_angles(data, ray))
		// 	return ;
	}
	// if (!side)
	// 	ray->len = ray->vlen, 
	ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
}



int	create_rays(t_data *data)
{
	// t_ray	ray;
	int		curr_ray;
	double	angle_ratio;
	
	curr_ray = 0;
	angle_ratio = 0.140625;
	while (curr_ray < data->main_img.nb_rays)
	{
		ft_memset(&data->main_img.rays[curr_ray], 0, sizeof(t_ray));
		find_next_wall(data, &data->main_img.rays[curr_ray], curr_ray * angle_ratio);
		// display_rays(data);
		curr_ray++;
	}
	return (0);
}
























// double fix_ang(double a)
// {
//     while (a > 359)
//         a -= 360;
//     while (a < 0)
//         a += 360;
//     return a;
// }

// double deg_to_rad(double degrees)
// {
//     return degrees * PI / 180.0;
// }

// void find_point_on_section(t_ray *ray, double len)
// {
//     ray->len += len;
//     ray->end.x = round(ray->end.x + len * ray->len_one_u.x);
//     ray->end.y = round(ray->end.y - len * ray->len_one_u.y);
// }

// int check_angles(t_data *data, t_ray *ray)
// {
//     t_point	first;
// 	t_point	second;

//     first.x = (int)(ray->end.x);
//     first.y = (int)(ray->end.y);
//     second.x = (int)(ray->end.x);
//     second.y = (int)(ray->end.y);
//     if (ray->angle_deg > 180)
//         first.y--;
//     else
//         first.y++;

//     if (ray->end.x < data->player.pos.x)
//         second.x++;
//     else if (ray->end.x > data->player.pos.x)
// 	{
// 	    second.x--;

// 	}
// 	// printf("first x: %f Y:%f\n", first.x, first.y);
//     if (data->map[(int)first.y][(int)first.x] == '1'
// 		&& data->map[(int)second.y][(int)second.x] == '1')
//         return 1;
//     return 0;
// }

// // t_point check_next_edges(t_data *data, t_ray *ray)
// // {
// // 	t_point step;
	
    

// //     // ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
// //     // ray->vlen.y = delta.y * ray->hypo_len_one_u.y;

// //     if ((ray->vlen.x < ray->vlen.y))
// //         return (find_point_on_section(ray, ray->vlen.x), step);
// //     else
// //         return (find_point_on_section(ray, ray->vlen.y), step);
// // }

// void find_next_wall(t_data *data, t_ray *ray, double curr_ray)
// {
// 	// double   cameraFraction;
// 	t_point	    step;
//     t_point     delta;
// 	t_point		map;
// 	int			side;

// 	map.x = (int)data->player.pos.x;
// 	map.y = (int)data->player.pos.y;
//     ray->angle_deg = fix_ang(data->player.direction + curr_ray - FOV * 0.5);
//     ray->angle_rad = deg_to_rad(ray->angle_deg);
//     ray->len_one_u.x = cos(ray->angle_rad);
//     ray->len_one_u.y = sin(ray->angle_rad);	
//  	// cameraFraction = curr_ray / data->win.w * 2 - 1;   
// 	ray->end.x = data->player.pos.x;
//     ray->end.y = data->player.pos.y;
// 	// ray->len_one_u.x += -sin(deg_to_rad(data->player.direction)) * cameraFraction;
// 	// ray->len_one_u.y += cos(deg_to_rad(data->player.direction)) * cameraFraction;
//     ray->hypo_len_one_u.x = sqrt(1 + pow(ray->len_one_u.y, 2) / pow(ray->len_one_u.x, 2));
//     ray->hypo_len_one_u.y = sqrt(1 + pow(ray->len_one_u.x, 2) / pow(ray->len_one_u.y, 2));
//     if (ray->angle_deg < 180)
// 	{
// 		step.y = -1;
//     	delta.y = ray->end.y - (int)ray->end.y;
// 	}
//     else
//     {
// 		step.y = 1;
// 		delta.y = ceil(ray->end.y) - ray->end.y;
// 	}

//     if ((ray->angle_deg > 90 && ray->angle_deg < 270))
//     {
// 		step.x = -1;
// 		delta.x = ray->end.x - (int)ray->end.x;
// 	}
//     else
//     {
// 		step.x = 1;
// 		delta.x = ceil(ray->end.x) - ray->end.x;
// 	}
// 	printf("delta x:%f y:%f\n", delta.x, delta.y);
// 	ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
// 	ray->vlen.y = delta.y * ray->hypo_len_one_u.y;
//     while (data->map[(int)(ray->end.y)][(int)(ray->end.x)] != '1')
// 	{
// 		if (ray->vlen.x < ray->vlen.y)
//         {
// 			ray->vlen.x += ray->hypo_len_one_u.x;
// 			map.x += step.x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			ray->vlen.y += ray->hypo_len_one_u.y;
// 			map.y += step.y;
// 			side = 1;
// 		}
// 		printf("map x:%f y:%f\n", map.x, map.y);
// 		if (data->map[(int)map.y][(int)map.x] == '1')
// 			break ;
//         // printf("curr %f\n", curr_ray);
// 		// if (curr_ray == 45)
// 		// 	printf("x : %f y : %f\n", ray->end.x, ray->end.y);
//         // step = check_next_edges(data, ray);
// 		// if (data->map[(int)(ray->end.y) + 1 * (int)step.y][(int)(ray->end.x) + 1 * (int)step.x] == '1')
// 		// 	return ;
//         // if (check_angles(data, ray))
//         //     return;
//     }
// 	if (!side)
// 		ray->len = (ray->vlen.x - ray->hypo_len_one_u.x) * 10;
// 	else
// 		ray->len = (ray->vlen.y - ray->hypo_len_one_u.y) * 10;
// 	printf("ray len %f\n", ray->len);
//     // ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
// }

// void display_rays(t_data *data, t_ray *ray) {
//     int i;
//     double ratio;
//     int num_points;

//     i = 0;
//     num_points = ray->len * 0.2;
//     while (i < num_points)
// 	{
//         ratio = (double)i / (double)(num_points - 1);
//         mlx_pixel_put(data->win.mlx_ptr, data->win.win_ptr, data->player.pos.x + ratio * (ray->end.x - data->player.pos.x),
//                       data->player.pos.y + ratio * (ray->end.y - data->player.pos.y), 0x7FFF00);
//         i++;
//     }
// }

// int	create_rays(t_data *data)
// {
// 	t_ray	ray;
// 	int		curr_ray;
// 	double	angle_ratio;

// 	curr_ray = 0;
// 	angle_ratio = 0.19411764705;
// 	while (curr_ray < data->main_img.nb_rays)
// 	{
// 		ft_memset(&ray, 0, sizeof(t_ray));
// 		find_next_wall(data, &ray, curr_ray * angle_ratio);
// 		data->main_img.rays_len[curr_ray] = ray.len;
// 		// printf("len %d i %d\n", data->main_img.rays_len[curr_ray], curr_ray);
// 		// display_rays(data, &ray);
// 		curr_ray++;
// 	}
// 	return (0);
// }