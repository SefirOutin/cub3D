/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/05 22:52:00 by soutin           ###   ########.fr       */
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
t_point	find_point_on_section(t_data *data, double x, double y, double angle_deg,
		double len_ray)
{
	t_point	result;
	double	angle_radians;

	// Convertir l'angle en radians
	angle_radians = degToRad(angle_deg);
	// Calculer les nouvelles coordonnées du point avec un rayon constant
	result.x = x + len_ray * cos(angle_radians);
	result.y = y - len_ray * sin(angle_radians);
	// printf("findddd x:%f y:%f\n", result.x, result.y);
	return (result);
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

t_point	check_next_edges(t_data *data, int curr_ray, double angle_deg, t_point current_pray)
{
	t_point	unit_size;
	t_point	length;
	t_point	delta;
	t_point	result;
	// double		i;
	// t_point	tmp_end;
	// y =tan(a)x +b 

	printf("x:%f y:%f\n", current_pray.x, current_pray.y);
	angle_deg = fix_ang(angle_deg);
	// printf("player x:%f y:%f\n", current_pray.x, current_pray.y);
	
	// calcule un vecteur normalisé (len à 1)
	length.x = cos(degToRad(angle_deg));
	length.y = sin(degToRad(angle_deg));
	// printf("end x:%f y:%f\n", length.x, length.y);
	// printf("direction deg:%f\n", angle_deg);
	
	// calcule la distance du joueur par rapport aux bords de la case que le joueur regarde (sert à unit_size)
	if (angle_deg > 0 && angle_deg < 180)
		delta.y = current_pray.y - (floor(current_pray.y / 50) * 50) + 1;
	else
		delta.y = (ceil(current_pray.y / 50) * 50) - current_pray.y ;
	if ((angle_deg > 90 && angle_deg < 270))
		delta.x = current_pray.x - (floor(current_pray.x / 50) * 50) + 1;
	else
		delta.x = (ceil(current_pray.x / 50) * 50) - current_pray.x;
	// printf("delta unit len x:%f y:%f\n", delta.x, delta.y);
	
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
	unit_size.x = delta.x * sqrt(1 + pow((length.y) / (length.x), 2));
	unit_size.y = delta.y * sqrt(1 + pow((length.x) / (length.y), 2));

	// vtmp_end = sqrt(pow(tmp_current_pray.x - data->player.px, 2) + pow(tmp_current_pray.y - data->player.py, 2));
	// printf("tmp_end :%f\n", vtmp_end);
	
	// printf("len vec 1x:%f len vec 1y:%f\n", unit_size.x, unit_size.y);
	if (unit_size.x < unit_size.y)
	{
		result = find_point_on_section(data, current_pray.x, current_pray.y, angle_deg, unit_size.x);
		printf("vx.x:%f y:%f\n", result.x, result.y);
	}
	else if (unit_size.x == unit_size.y)
	{
		if ((current_pray.x > result.x) && (angle_deg > 0 && angle_deg < 180))
			result.x -=1;
		else if ((current_pray.x < result.x) && (angle_deg > 0 && angle_deg < 180))
			result.x +=1;
		else if ()

		else
		
	}		
	else
	{
		result = find_point_on_section(data, current_pray.x, current_pray.y, angle_deg, unit_size.y);
		printf("vy.x:%f y:%f\n", result.x, result.y);
	}
	// printf("curr_ray p x:%f y:%f\n", result.x, result.y);
	return (result);
}

int	put_direction(t_data *data, double len_ray, int curr_ray)
{
	t_point		end;
	t_point		*section;
	int			i;

	i = 0;
	section = NULL;
	end.x = data->player.px;
	end.y = data->player.py;
	while (data->map[(int)(end.y / 50)][(int)(end.x / 50)] != '1')
	{
		end = check_next_edges(data, curr_ray, data->player.direction + curr_ray, end);
		
	}
	if (create_section(data, end, len_ray, &section))
		return (1);
	while (i < len_ray)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			section[i].x, section[i].y, 0x7FFF00);
		i++;
	}
	// printf("last x:%f y:%f\n", section[i - 1].x, section[i - 1].y);
	free(section);
	return (0);
}

int	rotate(t_data *data)
{
	int		len_ray;
	int		fov;
	int		i;

	i = 0;
	fov = 1;
	len_ray = 90;
	while (i < fov)
		if (put_direction(data, len_ray, i++) < 0)
			return (1);
	return (0);
}
