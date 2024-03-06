/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/06 23:42:58 by soutin           ###   ########.fr       */
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

int	put_ray(t_data *data)
{
	int	i;
	int	y;
	int	save;
	int	curr_ray;

	i = 0;
	while (1)
	{
		y = (data->player.py - 3 - i) / 50;
		save = data->map[y][(int)(data->player.px / 50)];
		// printf("save:%c\n", save);
		curr_ray = (data->player.py - i) - (((int)(data->player.py - i) / 50)
				* 50);
		// printf("curr_ray : %d\n", curr_ray);
		if (save == '1')
			break ;
		while (curr_ray > -1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->player.px,
				(int)data->player.py - i - curr_ray, 0x7FFF00);
			curr_ray--;
		}
		i++;
	}
	return (0);
}

double	degToRad(double degrees)
{
	return (degrees * PI / 180.0);
}

// Fonction pour trouver les coordonnées du point sur la section de l'angle
void	find_point_on_section(t_ray *ray, double len)
{
	// Calculer les nouvelles coordonnées du point avec un rayon constant
	ray->end.x = ray->end.x + len * cos(ray->angle_rad);
	ray->end.y = ray->end.y - len * sin(ray->angle_rad);
}

// Fonction pour créer une section entre deux points
int	create_section(t_data *data, t_point end, int numPoints, t_point **section)
{
	t_point	start;
	double	ratio;
	int		i;

	i = 0;
	start.x = data->player.px;
	start.y = data->player.py;
	*section = (t_point *)ft_calloc(numPoints, sizeof(t_point));
	if (!section)
		return (1);
	while (i < numPoints)
	{
		ratio = (double)i / (double)(numPoints - 1);
		(*section)[i].x = start.x + ratio * (end.x - start.x);
		(*section)[i].y = start.y +  ratio * (end.y - start.y);
		
		i++;
	}
	return (0);
}

int	check_next_edges(t_ray *ray)
{
	t_point	delta;
	// y =tan(a)x +b 

	// calcule la distance du joueur par rapport aux bords de la case que le joueur regarde (sert à vlen)
	if (ray->angle_deg > 0 && ray->angle_deg < 180)
		delta.y = ray->end.y - (floor(ray->end.y  * 0.02) * 50)+1;
	else
		delta.y = (ceil(ray->end.y * 0.02) * 50) - ray->end.y +1;
	if ((ray->angle_deg > 90 && ray->angle_deg < 270))
		delta.x = ray->end.x - (floor(ray->end.x * 0.02) * 50)+1 ;
	else
		delta.x = (ceil(ray->end.x * 0.02) * 50) - ray->end.x +1;
	// printf("delta unit len x:%f y:%f\n", delta.x, delta.y);
	
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
	ray->vlen.x = delta.x * ray->hypo_len.x;
	ray->vlen.y = delta.y * ray->hypo_len.y;
	printf("vlen x:%f Y:%f\n", ray->vlen.x, ray->vlen.y);
	if (ray->vlen.x == ray->vlen.y)
		printf("okkkkkkkkkk\n");
	if ((ray->vlen.x < ray->vlen.y))
		return (find_point_on_section(ray, ray->vlen.x), (int)ray->vlen.x);
	else
		return (find_point_on_section(ray, ray->vlen.y), (int)ray->vlen.y);
}

void	display_ray(t_data *data, t_point *section, int len)
{
	int			i;
	
	i = 7;
	while (i < len)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			section[i].x, section[i].y, 0x7FFF00);
		i++;
	}
	// printf("last x:%f y:%f\n", section[i - 1].x, section[i - 1].y);
}

void	find_next_wall(t_data *data, t_ray *ray, int curr_ray)
{
	ray->end.x = data->player.px;
	ray->end.y = data->player.py;
	ray->angle_deg = fix_ang(data->player.direction + curr_ray - 45);
	ray->angle_rad = degToRad(ray->angle_deg);
	ray->v_norm_len.x = cos(ray->angle_rad);
	ray->v_norm_len.y = sin(ray->angle_rad);
	ray->hypo_len.x =  sqrt(1 + pow((ray->v_norm_len.y) / (ray->v_norm_len.x), 2));
	ray->hypo_len.y = sqrt(1 + pow((ray->v_norm_len.x) / (ray->v_norm_len.y), 2));
	// printf("rad:%f deg%f len x:%f len y:%f\n", ray->angle_rad,ray->angle_deg, ray->v_norm_len.x, ray->v_norm_len.y);
	while (data->map[(int)(ray->end.y * 0.02)][(int)(ray->end.x * 0.02)] != '1')
	{
		ray->len += check_next_edges(ray);
		printf("player x:%f y:%f\n", data->player.px, data->player.py);
		printf("ray len %d\n", ray->len);
		printf("end x %f end y %f\n\n\n ",(ray->end.x*0.02),(ray->end.y*0.02));
		if (abs((int)ray->vlen.x * 10) - abs((int)ray->vlen.y * 10) > 10)
		{
			if (data->map[(int)(ray->end.y * 0.02)][(int)(ray->end.x * 0.02)] == '1')
			{
				
			}
		}
	}
}

int	create_ray(t_data *data, int curr_ray)
{
	t_ray	ray;
	
	ray.section = NULL;
	find_next_wall(data, &ray, curr_ray);
	if (create_section(data, ray.end, ray.len * 0.1, &ray.section))
		return (1);
	display_ray(data, ray.section, ray.len * 0.1);
	free(ray.section);
	return (0);
}

int	rotate(t_data *data)
{
	int		fov;
	int		i;

	i = 0;
	fov = 1;
	while (i < fov)
	{
		if (create_ray(data, i+=2) < 0)
			return (1);
	}
	return (0);
}
