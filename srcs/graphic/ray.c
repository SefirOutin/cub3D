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

int	check_next_case(t_data *data, int curr_ray, t_point end, double len_ray)
{
	t_point	new_end;
	double	len_ry;
	
	len_ry = len_ray * 0.1;
	new_end = find_point_on_section(data, end.x, end.y,
			(data->player.direction + curr_ray - 45), len_ry);
	printf("px:%f py:%f\n", data->player.px, data->player.py);
	printf("x:%f y:%f\n", (data->player.px + (new_end.x - data->player.px)) / 50, (data->player.py - (new_end.y - data->player.py)) / 50);
	if (data->map[(int)(data->player.py - (new_end.y - data->player.py)) / 50][(int)(data->player.px + (new_end.x - data->player.px)) / 50] == '0')
		printf("next case ok\n");
	return (0);
}

int	put_direction(t_data *data, double len_ray, int curr_ray)
{
	t_point		end;
	t_point		start;
	int			i;
	i = 0;
	end = find_point_on_section(data, data->player.px, data->player.py,
			(data->player.direction + curr_ray - 45 ), len_ray);
	check_next_case(data, curr_ray, end, len_ray);
	start.x = data->player.px;
	start.y = data->player.py;
	data->player.section[curr_ray] = create_section(start, end, len_ray);
	if (!data->player.section[curr_ray])
		return (free_section(data->player.section, curr_ray), -1);
	while (i < len_ray)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			data->player.section[curr_ray][i].x,
			data->player.section[curr_ray][i].y, 0x7FFF00);
		i++;
	}
	return (0);
}

void	erase_direction(t_data *data, int len_ray)
{
	int		i;
	int		curr_ray;
	
	curr_ray = 0;
	while (curr_ray < 90)
	{
		i = 0;
		while (i < len_ray)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,
				data->player.section[curr_ray][i].x,
				data->player.section[curr_ray][i].y, 0xFFFFFF);
			i++;
		}
		free(data->player.section[curr_ray]);
		curr_ray++;
	}
}

int	rotate(t_data *data, double rotation_angle)
{
	int	len_ray;
	int	fov;
	int	i;

	fov = 90;
	i = 0;
	len_ray = 50;
	data->player.direction += rotation_angle;
	i = 0;
	while (i < fov)
		if (put_direction(data, len_ray, i++) < 0)
			return (-1);
	return (0);
}
