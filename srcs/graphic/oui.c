/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/22 03:43:06 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp * 0.125);
	img->addr[pixel_index / (int)(img->bpp * 0.125)] = color;
}

void	verline(t_img *img, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		put_pixel_to_image(img,x,drawstart,color);
		drawstart++;
	}
}

void	create_vertical_line(t_img *img, t_point start, int len, int color)
{
	while (len--)
	{
		put_pixel_to_image(img, start.x, start.y, color);
		start.y++;
	}
}

void	create_wall(t_data *data, int coef_wall)
{
	int		color_wall;
	int		len_wall;
	t_point	start;

	color_wall = 0x0000FF;
	start.x = 0;
	len_wall = 0;
	while (start.x < 640 && len_wall < 1080)
	{
		len_wall = data->win.h / data->main_img.rays_len[(int)start.x];
		len_wall *= coef_wall;
		start.y = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_wall, color_wall);
		start.x++;
	}
}
void	create_floor(t_data *data, int coef_wall)
{
	int		len_wall;
	int		len_floor;
	t_point	start;

	start.x = 0;
	while (start.x < 640)
	{
		len_wall = data->win.h / data->main_img.rays_len[(int)start.x];
		len_wall *= coef_wall;
		start.y = (data->win.h / 2) + (len_wall / 2);
		len_floor = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_floor,
			data->main_img.floor_color);
		start.x++;
	}
}

void	create_sky(t_data *data, int coef_wall)
{
	int		len_wall;
	int		len_sky;
	t_point	start;

	start.x = 0;
	while (start.x < 640)
	{
		len_wall = data->win.h / data->main_img.rays_len[(int)start.x];
		start.y = 0;
		len_wall *= coef_wall;
		len_sky = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_sky,
			data->main_img.ceilling_color);
		start.x++;
	}
}

int	view(t_data *data)
{
	int coef_wall;

	coef_wall = 20;

	if (init_img(data, &data->main_img.view, data->win.w, data->win.h))
		return (-1);
	create_wall(data, coef_wall);
	create_floor(data, coef_wall);
	create_sky(data, coef_wall);
	return (0);
}