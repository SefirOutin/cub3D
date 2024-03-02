#include "cub3d.h"
#include <stdio.h>

// int	put_vector(t_data *data, int x, int y, int rotate)
// {
// 	int
// }

int	fix_ang(int a)
{
	if (a > 359)
		a -= 359;
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
		printf("save:%c\n", save);
		curr_ray = (data->player.py - i) - (((int)(data->player.py - i) / 50)
				* 50);
		printf("curr_ray : %d\n", curr_ray);
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

int	erased_ray(t_data *data)
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
		printf("save:%c\n", save);
		curr_ray = (data->player.py - i) - (((int)(data->player.py - i) / 50)
				* 50);
		printf("curr_ray : %d\n", curr_ray);
		if (save == '1')
			break ;
		while (curr_ray > -1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->player.px,
				(int)data->player.py - i - curr_ray, 0xFFFFFF);
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
	result.y = y + len_ray * sin(angle_radians);
	// if (data->map[(int)(result.y)][(int)(result.x)] == '0')
	// 	return (find_point_on_section(data, x, y, angle_deg, radius++));
	return (result);
}

// Fonction pour créer une section entre deux points
t_point	*create_section(t_point start, t_point end, int numPoints)
{
	t_point	*section;
	double	ratio;
	int		i;

	i = 0;
	section = (t_point *)ft_calloc(numPoints, sizeof(t_point));
	if (!section)
		return ((void *)0);
	while (i < numPoints)
	{
		ratio = (double)i / (double)(numPoints - 1);
		section[i].x = start.x + ratio * (end.x - start.x);
		section[i].y = start.y - ratio * (end.y - start.y);
		i++;
	}
	return (section);
}

int	check_next_case(t_data *data, int curr_ray, double angle_deg, int max_render_distance)
{
	// t_point	end;
	// double	angle_radians;
	t_point	unit_size;
	// double	vlength;
	t_point	tmp_end;
	t_point	start;

	printf("player x:%f y:%f\n", data->player.px, data->player.py);
	
	// calcule la distance du joueur par rapport à l'origine du carré actuel (sert à unit_size)
	start.x = data->player.px - (trunc(data->player.px / 50) * 50);
	start.y = (data->player.py - (trunc(data->player.py / 50) * 50));
	printf("startunitlen x:%f y:%f\n", start.x, start.y);
	
	// end = find_point_on_section(data, data->player.px, data->player.py,
	// 		(data->player.direction), 200);
	
	// calcule un vecteur normalisé (len à 1)
	tmp_end.x = data->player.px + cos(degToRad(data->player.direction));
	tmp_end.y = data->player.py + sin(degToRad(data->player.direction));
	
	
	// printf("end x:%f y:%f\n", data->player.px + (end.x - data->player.px), data->player.py - (end.y - data->player.py));

	// printf("end unit x:%f y:%f\n", data->player.px + cos(degToRad(data->player.direction)), data->player.py + sin(degToRad(data->player.direction)));
	
	// vlength = sqrt(pow(tmp_end.x - data->player.px, 2) + pow(tmp_end.y - data->player.py, 2));
	// printf("length :%f\n", vlength);
	
	// printf("uuuuu x:%f y:%f\n", end.x / length, end.y / length);
	
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
	unit_size.x = start.x * sqrt(1 + pow((tmp_end.x - data->player.px) / (tmp_end.y - data->player.py), 2));
	unit_size.y = start.y * sqrt(1 + pow((tmp_end.y - data->player.py) / (tmp_end.x - data->player.px), 2));
	printf("unit x:%f y:%f\n\n\n\n", unit_size.x, unit_size.y);
	return (0);
}

int	put_direction(t_data *data, double len_ray, int curr_ray)
{
	t_point		end;
	t_point		start;
	int			i;
	i = 6;

	end = find_point_on_section(data, data->player.px, data->player.py,
			(data->player.direction + curr_ray - 45), len_ray);
	
	start.x = data->player.px;
	start.y = data->player.py;
	data->player.section[curr_ray] = create_section(start, end, len_ray);
	if (!data->player.section[curr_ray])
		return (free_section(data->player.section, curr_ray), -1);
	// printf("first point drawn x:%f y :%f\n", data->player.section[curr_ray][i].x, data->player.section[curr_ray][i].y);
	while (i < len_ray)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			data->player.section[curr_ray][i].x,
			data->player.section[curr_ray][i].y, 0x7FFF00);
		// if (data->map[(int)(data->player.section[curr_ray][i].y / 50)][(int)(data->player.section[curr_ray][i].x / 50)] == '1')
		// 	data->map[(int)(data->player.section[curr_ray][i].y / 50)][(int)(data->player.section[curr_ray][i].x / 50)] = '5';
		// else
		// 	data->map[(int)(data->player.section[curr_ray][i].y / 50)][(int)(data->player.section[curr_ray][i].x / 50)] = '6';
		i++;
	}
	// ft_print_tab(data->map);
	return (0);
}

void	erase_direction(t_data *data, int len_ray)
{
	int		i;
	int		curr_ray;
	// int		j;
	
	// j = 0;
	// while (j < data->img.y_max)
	// {
	// 	i = 0;
	// 	while (i < data->img.x_max)
	// 	{
			
	// 		if (data->map[j][i] == '5')
	// 		{
	// 			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	// 					data->img.texture_map[0], (i * data->img.size_x), (-j
	// 						* data->img.size_y));
	// 			data->map[j][i] = '1';
	// 		}
	// 		else if (data->map[j][i] == '6')
	// 		{
	// 			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	// 					data->img.texture_map[2], (i * data->img.size_x), (-j
	// 						* data->img.size_y));
	// 			data->map[j][i] = '0';
	// 		}
	// 		i++;
	// 	}
	// 	j++;
	// }
	curr_ray = 0;
	while (curr_ray < 1)
	{
		i = 0;
		while (i < len_ray)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,
				data->player.section[44][i].x,
				data->player.section[44][i].y, 0xFFFFFF);
			i++;
		}
		curr_ray++;
		free(data->player.section[44]);
	}
}

int	rotate(t_data *data, double rotation_angle)
{
	int	len_ray;
	int	fov;
	int	i;

	fov = 90;
	len_ray = 25;
	data->player.direction += rotation_angle;
	i = 0;
	check_next_case(data, 44, data->player.direction, 24);
	// while (i < fov)
	if (put_direction(data, len_ray, 44) < 0)
		return (-1);
	return (0);
}
