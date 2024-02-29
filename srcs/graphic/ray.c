#include "cub3d.h"
#include <stdio.h>

// int	put_vector(t_data *data, int x, int y, int rotate)
// {
// 	int
// }

int	put_ray(t_data *data)
{
	int	i;
	int	y;
	int	save;
	int	count;

	i = 0;
	while (1)
	{
		y = (data->player.py - 3 - i) / 50;
		save = data->map[y][(int)(data->player.px / 50)];
		printf("save:%c\n", save);
		count = (data->player.py - i) - (((int)(data->player.py - i) / 50)
				* 50);
		printf("count : %d\n", count);
		if (save == '1')
			break ;
		while (count > -1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->player.px,
				(int)data->player.py - i - count, 0x7FFF00);
			count--;
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
	int	count;

	i = 0;
	while (1)
	{
		y = (data->player.py - 3 - i) / 50;
		save = data->map[y][(int)(data->player.px / 50)];
		printf("save:%c\n", save);
		count = (data->player.py - i) - (((int)(data->player.py - i) / 50)
				* 50);
		printf("count : %d\n", count);
		if (save == '1')
			break ;
		while (count > -1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->player.px,
				(int)data->player.py - i - count, 0xFFFFFF);
			count--;
		}
		i++;
	}
	return (0);
}
double	degToRad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

// Fonction pour trouver les coordonnées du point sur la section de l'angle
t_point	findPointOnSection(double x, double y, double angleDegrees,
		double radius)
{
	t_point	result;
	double	angleRadians;

	// Convertir l'angle en radians
	angleRadians = degToRad(angleDegrees);
	// Calculer les nouvelles coordonnées du point avec un rayon constant
	result.x = x + radius * cos(angleRadians);
	result.y = y + radius * sin(angleRadians);
	return (result);
}
// Fonction pour créer une section entre deux points
t_point	*createSection(t_point start, t_point end, int numPoints)
{
	t_point	*section;
	double	ratio;

	section = (t_point *)malloc(numPoints * sizeof(t_point));
	for (int i = 0; i < numPoints; ++i)
	{
		ratio = (double)i / (double)(numPoints - 1);
		section[i].x = start.x + ratio * (end.x - start.x);
		section[i].y = start.y + ratio * (end.y - start.y);
	}
	return (section);
}

// Fonction pour libérer la mémoire allouée pour la section
void	freeSection(t_point *section)
{
	free(section);
}

void	put_direction(t_data *data, double angleDegrees, int len_ray)
{
	t_point	end;
	t_point	start;
	t_point	*section;
	int		i;

	i = 0;
	end = findPointOnSection(data->player.px, data->player.py,
			data->player.direction + angleDegrees, len_ray);
	start.x = data->player.px;
	start.y = data->player.py;
	section = createSection(start, end, len_ray);
	while (i < len_ray)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, section[i].x, section[i].y,
			0x7FFF00);
		i++;
	}
	freeSection(section);
}

void	erase_direction(t_data *data, double angleDegrees, int len_ray)
{
	t_point	end;
	t_point	start;
	t_point	*section;
	int		i;

	i = 0;
	end = findPointOnSection(data->player.px, data->player.py,
			data->player.direction + angleDegrees, len_ray);
	start.x = data->player.px;
	start.y = data->player.py;
	section = createSection(start, end, len_ray);
	while (i < len_ray)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, section[i].x, section[i].y,
			0xFFFFFF);
		i++;
	}
	freeSection(section);
}
void	rotate(t_data *data, double angleDegrees)
{
	int	len_ray;
	int	fov;
	int	i;

	fov = 90;
	i = 0;
	len_ray = 100;
	while (i < fov)
		erase_direction(data, angleDegrees + i++, len_ray);
	data->player.direction += angleDegrees;
	i = 0;
	while (i < fov)
		put_direction(data, angleDegrees + i++, len_ray);
}
