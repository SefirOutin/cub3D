/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/27 15:28:30by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp * 0.125);
	img->addr[pixel_index / (int)(img->bpp * 0.125)] = color;
}

void	create_vertical_line(t_img *img, t_ipoint start, int len, int color)
{
	if (start.y < 0)
		return ;
	// printf("other start x %f y %f\n", start.x, start.y);
	while (len--)
	{
		if (start.y > WIN_H - 1)
			return ;
		// printf("x:%f, y:%f\n", start.x, start.y);
		put_pixel_to_image(img, start.x, start.y, color);
		start.y++;
	}
}

void	put_vertical_line_img_to_img(t_img *dst, t_img src, t_ipoint start,
		t_ipoint offset, int height)
{
	double			i;
	int				onset;
	unsigned int	color;
	double			gap_pourcent;
	double			gap_px;
	int				j;

	i = 0;
	j = 0;
	gap_pourcent = 0;
	gap_pourcent = (double)1 / (double)height;
	gap_px = (double)64 * gap_pourcent;
	 if (offset.x)
		onset = offset.x;
	 else
	 	onset = offset.y;
	if (start.y < 0)
		start.y = 0;
	// printf("wall after start x %f y %f\n", start.x, start.y);
	while (j < height)
	{
		if (start.y + i > WIN_H)
			return ;
		color = get_pixel_img(src, onset, i);
		put_pixel_img(dst, start.x, start.y + j, color);
		i += gap_px;
		j++;
	}
}

void	apply_texture(t_data *data, t_ray curr_ray, int wall_height, int x)
{
	t_ipoint	start;
	t_ipoint	offset;

	start.x = x;
	start.y = (data->win.h / 2) - (wall_height / 2);
		offset.x = (curr_ray.end.x - (int)curr_ray.end.x) * 64;
	// if (curr_ray.angle_deg > 135 && curr_ray.angle_deg < 205)
	// else
	// 	offset.x = ceil(curr_ray.end.x) - curr_ray.end.x * 64;
	offset.y = (curr_ray.end.y - (int)curr_ray.end.y) * 64;
	put_vertical_line_img_to_img(&data->main.view, data->main.textures[0],
			start, offset, wall_height);
}

void	create_wall(t_data *data, int coef_wall)
{
	int	wall_height;
	int	curr_ray;
	int	x;

	x = 0;
	curr_ray = data->main.nb_rays - 1;
	while (x < 640)
	{
		wall_height = data->win.h / ((data->main.rays[curr_ray].len));
		wall_height *= coef_wall;
		if (curr_ray == 320)
			printf("wall height %d\n", wall_height);
		apply_texture(data, data->main.rays[curr_ray], wall_height, x);
		curr_ray--;
		x++;
	}
}

void	create_floor_sky(t_data *data, int coef_wall)
{
	int			wall_height;
	int			len_floor_sky;
	t_ipoint	start;
	int			curr_ray;

	start.x = 0;
	curr_ray = data->main.nb_rays - 1;
	while (start.x < 640)
	{
		wall_height = data->win.h / (data->main.rays[curr_ray].len);
		wall_height *= coef_wall;
		start.y = (data->win.h / 2) + (wall_height / 2);
		len_floor_sky = (data->win.h / 2) - (wall_height / 2);
		create_vertical_line(&data->main.view, start, len_floor_sky,
				data->main.floor_color);
		start.y = 0;
		create_vertical_line(&data->main.view, start, len_floor_sky,
				data->main.ceilling_color);
		start.x++;
		curr_ray--;
	}
}

int	view(t_data *data)
{
	double	coef_wall;

	coef_wall = 1;
	if (init_img(data, &data->main.view, data->win.w, data->win.h))
		return (-1);
	create_wall(data, coef_wall);
	create_floor_sky(data, coef_wall);
	free(data->main.rays);
	return (0);
}
