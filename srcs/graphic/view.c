/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/26 18:13:48 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_quadrant(int angle)
{
	if (angle >= 0 && angle < 89)
		return (0);
	if (angle >=90  && angle < 180)
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
		return;
	while (len--)
	{
		// printf("x:%f, y:%f\n", start.x, start.y);
		put_pixel_to_image(img, start.x, start.y, color);
		start.y++;
		if (start.y > WIN_H - 1)
			return ;
	}
}

void	put_vertical_line_img_to_img(t_img *dst, t_img src, t_ipoint start, t_ipoint offset, int height)
{
	int				i;
	int 			offs;
	unsigned int	color;

	i = 0;
	if (offset.x)
		offs = offset.x;
	else
		offs = offset.y;
	while (i < height)
	{
		color = get_pixel_img(src, offs, i);
		if (start.y < 0 && start.y + i > WIN_H)
			return ;
		put_pixel_img(dst, start.x, start.y + i, color);
		i++;
	}
}

void	apply_texture(t_data *data, int wall_height, int x, int curr_ray)
{
	t_ipoint	start;
	t_ipoint	offset;
	
	start.x = x;
	if (curr_ray == 320)
			printf("wall height %f\n", ((double)wall_height / 64 * 100));
	start.y = (data->win.h / 2) - (wall_height / 2);
	offset.x = (data->main.rays[curr_ray].end.x - (int)data->main.rays[curr_ray].end.x) * 64;
	offset.y = (data->main.rays[curr_ray].end.y - (int)data->main.rays[curr_ray].end.y) * 64;
	put_vertical_line_img_to_img(&data->main.view, data->main.textures[0], start, offset, wall_height);
}

void	create_wall(t_data *data,int coef_wall)
{
	int	wall_height;
	int	curr_ray;
	int x;
	
	x = 0;
	curr_ray = data->main.nb_rays - 1;
	while (x < 640)
	{
		wall_height = data->win.h / ((data->main.rays[curr_ray].len));
		wall_height *= coef_wall;
		apply_texture(data, wall_height, x, curr_ray);
		curr_ray--;
		x++;
	}
	
}

void	create_floor(t_data *data,int coef_wall)
{
	int		wall_height;
	int		len_floor;
	t_ipoint	start;
	int		curr_ray;

	start.x = 0;
	curr_ray = data->main.nb_rays - 1;
	while (start.x < 640)
	{
		wall_height = data->win.h / (data->main.rays[curr_ray].len);
		wall_height *= coef_wall;
		start.y = (data->win.h / 2) + (wall_height / 2);
		len_floor = (data->win.h / 2) - (wall_height / 2);
		create_vertical_line(&data->main.view, start, len_floor,
		data->main.floor_color);
		start.x++;
		curr_ray--;
	}
}

void	create_sky(t_data *data,int coef_wall)
{
	int		wall_height;
	int		len_sky;
	t_ipoint	start;
	int		curr_ray;

	start.x = 0;
	curr_ray = data->main.nb_rays - 1;
	while (start.x < 640)
	{
		wall_height = data->win.h / (data->main.rays[curr_ray].len);
		start.y = 0;
		wall_height *= coef_wall;
		len_sky = (data->win.h / 2) - (wall_height / 2);
		create_vertical_line(&data->main.view, start, len_sky,
			data->main.ceilling_color);
		start.x++;
		curr_ray--;
	}
}

int	view(t_data *data)
{
	double coef_wall;

	coef_wall = 1;

	if (init_img(data, &data->main.view, data->win.w, data->win.h))
		return (-1);
	create_wall(data,coef_wall);
	create_floor(data,coef_wall);
	create_sky(data,coef_wall);
	free(data->main.rays);
	return (0);
}
