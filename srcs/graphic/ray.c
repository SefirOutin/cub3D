/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/21 15:56:57 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double fix_ang(double a)
{
    while (a > 359)
        a -= 360;
    while (a < 0)
        a += 360;
    return a;
}

double deg_to_rad(double degrees)
{
    return degrees * PI / 180.0;
}

void find_point_on_section(t_ray *ray, double len)
{
    ray->len += len;
    ray->end.x = round(ray->end.x + len * ray->len_one_u.x);
    ray->end.y = round(ray->end.y - len * ray->len_one_u.y);
}

int check_angles(t_data *data, t_ray *ray)
{
    t_point	first;
	t_point	second;

    first.x = (int)(ray->end.x);
    first.y = (int)(ray->end.y);
    second.x = (int)(ray->end.x);
    second.y = (int)(ray->end.y);
    if (ray->angle_deg > 180)
        first.y--;
    else
        first.y++;

    if (ray->end.x < data->player.pos.x)
        second.x++;
    else if (ray->end.x > data->player.pos.x)
	{
	    second.x--;

	}
	// printf("first x: %f Y:%f\n", first.x, first.y);
    if (data->map[(int)first.y][(int)first.x] == '1'
		&& data->map[(int)second.y][(int)second.x] == '1')
        return 1;
    return 0;
}

// t_point check_next_edges(t_data *data, t_ray *ray)
// {
// 	t_point step;
	
    

//     // ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
//     // ray->vlen.y = delta.y * ray->hypo_len_one_u.y;

//     if ((ray->vlen.x < ray->vlen.y))
//         return (find_point_on_section(ray, ray->vlen.x), step);
//     else
//         return (find_point_on_section(ray, ray->vlen.y), step);
// }

void find_next_wall(t_data *data, t_ray *ray, double curr_ray)
{
	// double   cameraFraction;
	t_point	    step;
    t_point     delta;
	t_point		map;
	int			side;

	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;
    ray->angle_deg = fix_ang(data->player.direction + curr_ray - FOV * 0.5);
    ray->angle_rad = deg_to_rad(ray->angle_deg);
    ray->len_one_u.x = cos(ray->angle_rad);
    ray->len_one_u.y = sin(ray->angle_rad);	
 	// cameraFraction = curr_ray / data->win.w * 2 - 1;   
	ray->end.x = data->player.pos.x;
    ray->end.y = data->player.pos.y;
	// ray->len_one_u.x += -sin(deg_to_rad(data->player.direction)) * cameraFraction;
	// ray->len_one_u.y += cos(deg_to_rad(data->player.direction)) * cameraFraction;
    ray->hypo_len_one_u.x = sqrt(1 + pow(ray->len_one_u.y, 2) / pow(ray->len_one_u.x, 2));
    ray->hypo_len_one_u.y = sqrt(1 + pow(ray->len_one_u.x, 2) / pow(ray->len_one_u.y, 2));
    if (ray->angle_deg > 0 && ray->angle_deg < 180)
	{
		step.y = -1;
    	delta.y = ray->end.y - (int)ray->end.y;
	}
    else
    {
		step.y = 1;
		delta.y = ceil(ray->end.y) - ray->end.y;
	}

    if ((ray->angle_deg > 90 && ray->angle_deg < 270))
    {
		step.x = -1;
		delta.x = ray->end.x - (int)ray->end.x;
	}
    else
    {
		step.x = 1;
		delta.x = ceil(ray->end.x) - ray->end.x;
	}
	ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
	ray->vlen.y = delta.y * ray->hypo_len_one_u.y;
    while (data->map[(int)(ray->end.y)][(int)(ray->end.x)] != '1')
	{
		if (ray->vlen.x < ray->vlen.y)
        {
			ray->vlen.x += ray->hypo_len_one_u.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			ray->vlen.y += ray->hypo_len_one_u.y;
			map.y += step.y;
			side = 1;
		}
		if (data->map[(int)map.y][(int)map.x] == '1')
			break ;
        // printf("curr %f\n", curr_ray);
		// if (curr_ray == 45)
		// 	printf("x : %f y : %f\n", ray->end.x, ray->end.y);
        // step = check_next_edges(data, ray);
		// if (data->map[(int)(ray->end.y) + 1 * (int)step.y][(int)(ray->end.x) + 1 * (int)step.x] == '1')
		// 	return ;
        // if (check_angles(data, ray))
        //     return;
    }
	if (!side)
		ray->len = ray->vlen.x - ray->hypo_len_one_u.x;
	else
		ray->len = ray->vlen.y - ray->hypo_len_one_u.y;
    // ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
}

void display_rays(t_data *data, t_ray *ray) {
    int i;
    double ratio;
    int num_points;

    i = 0;
    num_points = ray->len * 0.2;
    while (i < num_points)
	{
        ratio = (double)i / (double)(num_points - 1);
        mlx_pixel_put(data->win.mlx_ptr, data->win.win_ptr, data->player.pos.x + ratio * (ray->end.x - data->player.pos.x),
                      data->player.pos.y + ratio * (ray->end.y - data->player.pos.y), 0x7FFF00);
        i++;
    }
}

int	create_rays(t_data *data)
{
	t_ray	ray;
	int		curr_ray;
	double	angle_ratio;

	curr_ray = 0;
	angle_ratio = 0.19411764705;
	while (curr_ray < data->main_img.nb_rays)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		find_next_wall(data, &ray, curr_ray * angle_ratio);
		data->main_img.rays_len[curr_ray] = ray.len;
		// printf("len %d i %d\n", data->main_img.rays_len[curr_ray], curr_ray);
		// display_rays(data, &ray);
		curr_ray++;
	}
	return (0);
}