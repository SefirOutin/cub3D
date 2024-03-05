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

double	degToRad(double degrees)
{
	return (degrees * PI / 180.0);
}

// Fonction pour trouver les coordonnées du point sur la section de l'angle
void	find_point_on_section(t_data *data, double x, double y, double angle_deg,
		double len_ray, t_point *end)
{
	// t_point	result;
	double	angle_radians;

	// Convertir l'angle en radians
	angle_radians = degToRad(angle_deg);
	// Calculer les nouvelles coordonnées du point avec un rayon constant
	end->x = x + len_ray * cos(angle_radians);
	end->y = y + len_ray * sin(angle_radians);
	// result
	// if (data->map[(int)(result.y)][(int)(result.x)] == '0')
	// 	return (find_point_on_section(data, x, y, angle_deg, radius++));
	// return (result);
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
		section[i].y = start.y +  ratio * (end.y - start.y);
		i++;
	}
	return (section);
}

t_point	check_next_case(t_data *data, int curr_ray, double angle_deg, int max_render_distance)
{
	t_point	end;
	t_point	unit_size;
	t_point	length;
	t_point	delta;
	// double		i;
	// t_point	tmp_end;
	// y =tan(a)x +b 

	angle_deg = fix_ang(angle_deg);
	printf("player x:%f y:%f\n", data->player.px, data->player.py);
	// calcule un vecteur normalisé (len à 1)
	length.x = cos(degToRad(angle_deg));
	length.y = sin(degToRad(angle_deg));
	printf("end x:%f y:%f\n", length.x, length.y);

	// tmp_end.x = tmp_end.x - data->player.px;
	// tmp_end.y = tmp_end.y - data->player.py;
	printf("direction deg:%f\n", angle_deg);
	
	// calcule la distance du joueur par rapport à l'origine du carré actuel (sert à unit_size)
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer 
	if (angle_deg > 0 && angle_deg < 180)
		delta.y = data->player.py - (floor(data->player.py / 50) * 50);
	else
		delta.y = (ceil(data->player.py / 50) * 50) - data->player.py;
	if ((angle_deg > 90 && angle_deg < 270))
		delta.x = data->player.px - (floor(data->player.px / 50) * 50);
	else
		delta.x = (ceil(data->player.px / 50) * 50) - data->player.px;
	printf("deltaunitlen x:%f y:%f\n", delta.x, delta.y);
	unit_size.x = delta.x * sqrt(1 + pow((length.y) / (length.x), 2));
	unit_size.y = delta.y * sqrt(1 + pow((length.x) / (length.y), 2));

	// vtmp_end = sqrt(pow(tmp_end.x - data->player.px, 2) + pow(tmp_end.y - data->player.py, 2));
	// printf("tmp_end :%f\n", vtmp_end);
	
	printf("len vec 1x:%f len vec 1y:%f\n", unit_size.x, unit_size.y);
	if (unit_size.x < unit_size.y)
	{
		find_point_on_section(data, data->player.px, data->player.py, angle_deg, unit_size.x, &end);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px + (end.x - data->player.px), data->player.py - (end.y - data->player.py), 0xFF0000);
		printf("vx.x:%f vx.y:%f\n", end.x, end.y);
		printf("len 1x plus petit\n");
	}
	else
	{

		find_point_on_section(data, data->player.px, data->player.py, angle_deg, unit_size.y, &end);
		printf("vy.x:%f vy.y:%f\n", end.x, end.y);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player.px + (end.x - data->player.px), data->player.py - (end.y - data->player.py), 0xFF0000);
		printf("len 1y plus petit\n");
		
	}
	// end.x = 
	printf("\n\n");
	return (end);
}

int	put_direction(t_data *data, double len_ray, int curr_ray)
{
	t_point		end;
	t_point		delta;
	int			i;
	t_point		save;

	i = 0;
	end = check_next_case(data, curr_ray, data->player.direction + curr_ray - 45, 25);
	delta.x = data->player.px;
	delta.y = data->player.py;
	data->player.section[curr_ray] = create_section(delta, end, len_ray);
	if (!data->player.section[curr_ray])
		return (free_section(data->player.section, curr_ray), -1);
	while (i < len_ray)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			data->player.section[curr_ray][i].x,
			data->player.section[curr_ray][i].y, 0x7FFF00);
		save.x = data->player.section[curr_ray][i].x;
		save.y = data->player.section[curr_ray][i].y;
		if (data->map[(int)save.y / 50][(int)save.x / 50] == '1')
			data->map[(int)save.y / 50][(int)save.x / 50] = '5';
		else if (ft_strchr("ONSWE", data->map[(int)save.y / 50][(int)save.x / 50]))
			data->map[(int)save.y / 50][(int)save.x / 50] = '6';
		i++;
	}
	// ft_print_tab(data->map);
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
	len_ray = 25;
	data->player.direction += rotation_angle;
	i = 0;
	while (i < fov)
		if (put_direction(data, len_ray, i++) < 0)
			return (-1);
	return (0);
}
