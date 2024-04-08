/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/04/08 21:10:16 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_texture(t_data *data, t_ray curr_ray, int wall_height, int x);
void	create_wall(t_data *data, int coef_wall);
void	create_floor_sky(t_data *data, int coef_wall);

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

void	put_vertical_line_img_to_img(t_data *data, t_img src,
		int offset_and_x[2], int height)
{
	t_ipoint	wall_start_end;
	double		i;
	double		gap_px;

	i = 0;
	gap_px = (double)64 / (double)height;
	wall_start_end.x = (data->win.h * 0.5) - (height * 0.5);
	if (wall_start_end.x < 0)
	{
		i = abs(wall_start_end.x) * gap_px;
		wall_start_end.x = 0;
	}
	wall_start_end.y = (data->win.h * .5) + (height * 0.5);
	if (wall_start_end.y > data->win.h - 1)
		wall_start_end.y = data->win.h - 1;
	while (wall_start_end.x < wall_start_end.y)
	{
		put_pixel_to_image(&data->main.view, offset_and_x[1], wall_start_end.x,
			get_pixel_img(src, offset_and_x[0], i));
		i += gap_px;
		wall_start_end.x++;
	}
}

void	apply_texture(t_data *data, t_ray curr_ray, int wall_height, int x)
{
	int		offset_and_x[2];
	t_img	texture;

	offset_and_x[1] = x;
	if (!curr_ray.side)
	{
		if (curr_ray.end.x < data->player.pos.x)
			texture = data->main.textures[3];
		else
			texture = data->main.textures[1];
		offset_and_x[0] = (curr_ray.end.y - (int)curr_ray.end.y) * 64;
	}
	else
	{
		if (curr_ray.end.y < data->player.pos.y)
			texture = data->main.textures[0];
		else
			texture = data->main.textures[2];
		offset_and_x[0] = (curr_ray.end.x - (int)curr_ray.end.x) * 64;
	}
	if ((!curr_ray.side && curr_ray.end.x < data->player.pos.x)
		|| (curr_ray.side && curr_ray.end.y > data->player.pos.y))
		offset_and_x[0] = 64 - offset_and_x[0];
	put_vertical_line_img_to_img(data, texture, offset_and_x, wall_height);
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
		wall_height = data->win.h / (data->main.rays[curr_ray--].len);
		wall_height *= coef_wall;
		start.y = (data->win.h / 2) + (wall_height / 2);
		len_floor_sky = (data->win.h / 2) - (wall_height / 2);
		if (len_floor_sky <= 0 && ++start.x)
			continue ;
		if (start.y < data->win.h)
			draw_vertical_line(&data->main.view, start, len_floor_sky,
				data->main.floor_color);
		start.y = 0;
		draw_vertical_line(&data->main.view, start, len_floor_sky,
			data->main.ceilling_color);
		start.x++;
	}
}
