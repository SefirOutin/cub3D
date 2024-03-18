/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/16 14:36:49by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp / 8);
	((img->addr))[pixel_index / (int)(img->bpp / 8)] = color;
}

// int	view(t_data *data)
//{
//	int		x;
//	double	y_top;
//	double	y_bot;
//	double	wall_height;
//	int		half_height;
//	int		ratio;
//	int		i;
//
//	ratio = data->win.w / data->main_img.nb_rays;
//	half_height = data->win.h * 0.5;
//	data->main_img.view = init_img(data, data->win.w, data->win.h);
//	x = 0;
//	if (!data->main_img.view.img)
//		return (1);
//	while (x < data->win.w)
//	{
//		wall_height = data->win.h / data->main_img.rays_len[x / ratio] * 3;
//		y_bot = half_height;
//		y_top = half_height;
//		while (wall_height-- && y_top >= 0)
//		{
//			i = 0;
//			while (i < ratio)
//			{
//				put_pixel_to_image(&data->main_img.view, x + i, y_bot,
//					0x0000FF);
//				put_pixel_to_image(&data->main_img.view, x + i, y_top,
//					0x0000FF);
//				i++;
//			}
//			y_bot++;
//			y_top--;
//		}
//		while (y_bot < data->win.h)
//		{
//			i = 0;
//			while (i < ratio)
//				put_pixel_to_image(&data->main_img.view, x + i++, y_bot,
//					data->main_img.floor_color);
//			y_bot++;
//		}
//		while (y_top > -1)
//		{
//			i = 0;
//			while (i < ratio)
//				put_pixel_toぷmage(&data->main_img.view, x + i++, y_top,
//					data->main_img.ceilling_color);
//			y_top--;
//		}
//		x += ratio;
//	}
//	// mlx_destroy_image(data->mlx_ptr, data->main_img.view.img);
//	return (0);
//}

void	create_vertical_line(t_img *img, t_point start, int len, int color)
{
	while (len--)
	{
		put_pixel_to_image(img, start.x, start.y, color);
		start.y++;
	}
}

void	create_wall(t_data *data,int coef_wall)
{
	int		color_wall;
	int		len_wall;
	t_point	start;

	color_wall = 0x0000FF;
	start.x = 0;
	len_wall = 0;
	while (start.x < 640 && len_wall < 1080)
	{
		len_wall = data->win.h / ((data->main_img.rays_len[(int)start.x]));
		len_wall *= coef_wall;
		start.y = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_wall, color_wall);
		start.x++;
	}
}
void	create_floor(t_data *data,int coef_wall)
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

void	create_sky(t_data *data,int coef_wall)
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

	coef_wall = 10;
	
	if (init_img(data, &data->main_img.view, data->win.w, data->win.h))
		return (-1);
	create_wall(data,coef_wall);
	create_floor(data,coef_wall);
	create_sky(data,coef_wall);
	return (0);
}