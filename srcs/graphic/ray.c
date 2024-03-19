/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:27 by soutin            #+#    #+#             */
/*   Updated: 2024/03/19 20:30:08 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
 
fxpoint	fix_ang(fxpoint a)
{
	if (a > 359 << SHIFT_AMOUNT)
		a -= 360 << SHIFT_AMOUNT;
	if (a < 0 << SHIFT_AMOUNT)
		a += 360 << SHIFT_AMOUNT;
	return (a);
}

fxpoint	deg_to_rad(fxpoint degrees)
{
	return ((fxpoint)((degrees) * PI / 180.0));
}

// Fonction pour trouver les coordonnées du point sur la section de l'angle
void	find_point_on_section(t_ray *ray, fxpoint len)
{
	ray->len += len;
	ray->end.x = ray->end.x + len * ray->len_one_u.x;
	ray->end.y = ray->end.y - len * ray->len_one_u.y;
}

int	diff_nearest_50x(int x)
{
	int	nearestMultiple;
	int	difference;

	// Calcul du multiple de 50 le plus proche
	nearestMultiple = 50 * (x / 50);
	// Calcul de la différence
	difference = x - nearestMultiple;
	if (difference > 25)
		return (50 - difference);
	return (difference);
}

int	get_quadrant(int angle)
{
	if (angle >= 0 && angle < 89)
		return (0);
	if (angle >= 90 && angle < 180)
		return (1);
	if (angle >= 180 && angle < 270)
		return (2);
	if (angle >= 270 && angle < 360)
		return (3);
	return (-1);
}

t_point get_cell(t_point  point) {
    t_point  cell;
    cell.x = point.x / SHIFT_MASK;
    cell.y = point.y / SHIFT_MASK;
    return cell;
}

// Function to get the offset of a point within a cell
t_point  get_offset(t_point  point) {
    t_point  offset;
    offset.x = point.x - (get_cell(point).x * SHIFT_MASK);
    offset.y = point.y - (get_cell(point).y * SHIFT_MASK);
    return offset;
}

int	check_next_edges(t_data *data, t_ray *ray)
{
	t_point	delta;
	static int i;

	// calcule la distance du joueur par rapport aux bords de la case que le joueur regarde (sert à vlen)
	if (ray->angle_deg < shift(180))
		delta.y = double_to_fixed(fixed_to_double(ray->end.y) - floor(fixed_to_double(ray->end.y)) + 1);
	else
		delta.y = double_to_fixed(fixed_to_double(ceil(ray->end.y)) - fixed_to_double(ray->end.y) + 1);
	if (ray->angle_deg > shift(90) && ray->angle_deg < shift(269))
		delta.x = double_to_fixed(fixed_to_double(ray->end.x) - floor(fixed_to_double(ray->end.x)) + 1);
	else
		delta.x = double_to_fixed(fixed_to_double(ceil(ray->end.x)) - fixed_to_double(ray->end.x) + 1);
	// delta = get_offset(ray->end);
	if (i++ < 10)
	{
		printf("curr x:%f y:%f\n", fixed_to_double(ray->end.x), fixed_to_double(ray->end.y));
		printf("floor :%f\n", floor(fixed_to_double(ray->end.y)));
		printf("delta x:%f y:%f\n\n", fixed_to_double(delta.x), fixed_to_double(ray->end.y));
	}
	// calcule du vecteur pour prochain x entier et prochain y entier pour ensuite les comparer
	ray->vlen.x = delta.x * ray->hypo_len_one_u.x;
	ray->vlen.y = delta.y * ray->hypo_len_one_u.y;
	// printf("vlen x:%f Y:%f\n", ray->vlen.x, ray->vlen.y);
	if (ray->vlen.x < ray->vlen.y)
		return (find_point_on_section(ray, ray->vlen.x), ray->vlen.x);
	else
		return (find_point_on_section(ray, ray->vlen.y), ray->vlen.y);
}



int	check_angles(t_data *data, t_ray *ray)
{
	t_point	first;
	t_point	second;

	first.x = unshift(ray->end.x);
	first.y = unshift(ray->end.y);
	second.x = unshift(ray->end.x);
	second.y = unshift(ray->end.y);
	if (ray->angle_deg > shift(180))
		first.y--;
	else
		first.y++;
	if (ray->end.x < data->player.pos.x)
		second.x++;
	else if (ray->end.x > data->player.pos.x)
		second.x--;
	if (data->map[first.y][first.x] == '1'
		&& data->map[second.y][second.x] == '1')
		return (1);
	return (0);
}

void	find_next_wall(t_data *data, t_ray *ray, fxpoint curr_ray)
{
	ray->angle_deg = fix_ang(data->player.direction - FOV * 0.5 + curr_ray );
	ray->angle_rad = deg_to_rad(ray->angle_deg);
	ray->len_one_u.x = double_to_fixed(cos(fixed_to_double(ray->angle_rad)));
	ray->len_one_u.y = double_to_fixed(sin(fixed_to_double(ray->angle_rad)));
	ray->end.x = data->player.pos.x;
	ray->end.y = data->player.pos.y;
	printf("player x :%f y:%f\n", fixed_to_double(ray->end.x), fixed_to_double(ray->end.y));
	ray->hypo_len_one_u.x = sqrt(shift(1) + pow(((ray->len_one_u.y))
				/ (ray->len_one_u.x), 2));
	ray->hypo_len_one_u.y = sqrt(shift(1) + pow(((ray->len_one_u.x))
				/ (ray->len_one_u.y), 2));
	// printf("x : %f y:%f\n", fixed_to_double(ray->end.x), fixed_to_double(ray->end.y));
	while ((data->map[(int)fixed_to_double(ray->end.y)][(int)fixed_to_double(ray->end.x)] != '1'))
	{
		check_next_edges(data, ray);
		if (check_angles(data, ray))
			return ;
	}
	// ray->len *= cos(ray->angle_rad - deg_to_rad(data->player.direction));
}

void	display_rays(t_data *data, t_ray *ray)
{
	int		i;
	double	ratio;
	int		num_points;

	i = 0;
	num_points = ray->len * 0.2;
	while (i < num_points)
	{
		ratio = (double)i / (double)(num_points - 1);
		mlx_pixel_put(data->win.mlx_ptr, data->win.win_ptr, data->player.pos.x
			+ ratio * (ray->end.x - data->player.pos.x), data->player.pos.y
			+ ratio * (ray->end.y - data->player.pos.y), 0x7FFF00);
		i++;
	}
}

int	create_rays(t_data *data)
{
	t_ray	ray;
	int		curr_ray;
	double	angle_ratio;

	curr_ray = 0;
	angle_ratio = double_to_fixed(0.28125);
	while (curr_ray < data->main_img.nb_rays)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		find_next_wall(data, &ray, shift(curr_ray) * angle_ratio);
		data->main_img.rays_len[curr_ray] = ray.len;
		// printf("len %d\n", data->main_img.rays_len[curr_ray]);
		// display_rays(data, &ray);
		curr_ray++;
	}
	return (0);
}
