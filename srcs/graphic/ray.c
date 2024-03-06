/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/06 15:57:03 by soutin           ###   ########.fr       */
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
void	find_point_on_section(t_point *end, double angle, double len_ray)
{
	double	angle_radians;

	// Convertir l'angle en radians
	angle_radians = degToRad(angle);
	// Calculer les nouvelles coordonnées du point avec un rayon constant
	end->x = end->x + len_ray * cos(angle_radians);
	end->y = end->y - len_ray * sin(angle_radians);
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

int	check_next_edges(t_data *data, double angle_deg, t_point *curr_start)
{
	t_point	vlen;
	t_point	length;
	t_point	delta;
	// y =tan(a)x +b 

	printf("curr_start x:%f y:%f\n", curr_start->x, curr_start->y);
	angle_deg = fix_ang(angle_deg);
	printf("player x:%f y:%f\n", data->player.px, data->player.py);
	
	// calcule un vecteur normalisé (len à 1)
	length.x = cos(degToRad(angle_deg));
	length.y = sin(degToRad(angle_deg));
	// printf("end x:%f y:%f\n", length.x, length.y);
	printf("direction deg:%f\n", angle_deg);
	
	// calcule la distance du joueur par rapport aux bords de la case que le joueur regarde (sert à vlen)
	if (angle_deg > 0 && angle_deg < 180)
		delta.y = curr_start->y - (floor(curr_start->y / 50) * 50) + 1;
	else
		delta.y = (ceil(curr_start->y / 50) * 50) - curr_start->y + 1;
	if ((angle_deg > 90 && angle_deg < 270))
		delta.x = curr_start->x - (floor(curr_start->x / 50) * 50) + 1;
	else
		delta.x = (ceil(curr_start->x / 50) * 50) - curr_start->x + 1;
	printf("delta unit len x:%f y:%f\n", delta.x, delta.y);
	
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
	vlen.x = delta.x * sqrt(1 + pow((length.y) / (length.x), 2));
	vlen.y = delta.y * sqrt(1 + pow((length.x) / (length.y), 2));
	printf("vlen x:%f y:%f\n", vlen.x, vlen.y);
	if (isnan(vlen.x))
		printf("x is Nan\n");
	if (isnan(vlen.y))
		printf("y is Nan\n");
	// vtmp_end = sqrt(pow(tmp_curr_start->x - data->player.px, 2) + pow(tmp_curr_start->y - data->player.py, 2));
	// printf("tmp_end :%f\n", vtmp_end);
	
	// if (!vlen.y)
	// 	return (result);
	// if (!vlen.x)
	// 	return (result1);
	if ((vlen.x < vlen.y))
	{
		find_point_on_section(curr_start, angle_deg, vlen.x);
		printf("len x <\n");
		return ((int)vlen.x);
	}	
	else
	{
		find_point_on_section(curr_start, angle_deg, vlen.y);
		printf("len y <\n");
		return ((int)vlen.y);
	}
	// printf("curr_ray p x:%f y:%f\n", result.x, result.y);
}

int	put_direction(t_data *data, int curr_ray)
{
	t_point		end;
	t_point		*section;
	int			i;
	int			len;

	i = 0;
	section = NULL;
	len = 0;
	end.x = data->player.px;
	end.y = data->player.py;
	while (data->map[(int)(end.y / 50)][(int)(end.x / 50)] != '1')
	{
		len += check_next_edges(data, data->player.direction + curr_ray, &end);
		printf("coor map X:%d y:%d\n\n", (int)(end.x / 50), (int)(end.y / 50));
		
	}
	if (create_section(data, end, len, &section))
		return (1);
	while (i < len)
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
	int		fov;
	int		i;

	i = 0;
	fov = 90;
	while (i < fov)
		if (put_direction(data, i++) < 0)
			return (1);
	return (0);
}
