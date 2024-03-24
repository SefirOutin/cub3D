/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/24 15:13:04 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img->line_l + x * (int)(img->bpp * 0.125);
	img->addr[pixel_index / (int)(img->bpp * 0.125)] = color;
}

void	create_vertical_line(t_img *img, t_point start, int len, int color)
{
	while (len--)
	{
		// printf("x:%f, y:%f\n", start.x, start.y);
		put_pixel_to_image(img, start.x, start.y, color);
		start.y++;
	}
}

void	draw_wall(t_data *data, int x, int ys[2], int ratio, int curr_ray)
{
	int	half_height;
	int	wall_height;
	int	i;
	
	half_height = data->win.h * 0.5;
	ys[0] = half_height;
	ys[1] = half_height;
	wall_height = data->win.h / (data->main_img.rays[curr_ray].len * 5);
	// if (curr_ray == 320)
		// printf("wall h %d\n\n", wall_height);
	while (wall_height-- && ys[1] >= 0 && ys[0] <= data->win.h)
	{
		// printf("x %d y :%d\n", x, ys[0]);
		i = 0;
		while (i < ratio)
		{
			put_pixel_to_image(&data->main_img.view, x + i, ys[0],
				0x0000FF);
			put_pixel_to_image(&data->main_img.view, x + i, ys[1],
				0x0000FF);
			i++;
		}
		(ys[0])++;
		(ys[1])--;
	}	
}

void	draw_ceil_and_floor(t_data *data, int x, int ys[2], int ratio)
{
	int	i;
	
	while (ys[0] < data->win.h)
	{
		i = 0;
		while (i < ratio)
		{
			put_pixel_to_image(&data->main_img.view, x + i, ys[0],
				data->main_img.floor_color);
			put_pixel_to_image(&data->main_img.view, x + i++, ys[1],
				data->main_img.ceilling_color);
		}
		ys[0]++;
		ys[1]--;
	}
	
}
// y[0] = y_floor y[1] == y_ceilling
int	view(t_data *data)
{
	int	x;
	int	ys[2];
	int	ratio;
	int	curr_ray;
	// int	i;

	// i = 0;
	x = 0;
	ratio = data->win.w / data->main_img.nb_rays;
	// printf("nb %d\n", data->main_img.nb_rays);
	curr_ray = data->main_img.nb_rays - 1;
	if (init_img(data, &data->main_img.view, data->win.w, data->win.h))
		return (1);
	while (x < data->win.w)
	{
		draw_wall(data, x, ys, ratio, curr_ray);
		draw_ceil_and_floor(data, x, ys, ratio);
		x += ratio;
		curr_ray--;
	}
	// while (i < 300)
	// {
	// 	put_pixel_to_image(&data->main_img.view, data->win.w / 2 - 1, i, 0x000000);
	// 	put_pixel_to_image(&data->main_img.view, data->win.w / 2, i, 0x000000);
	// 	put_pixel_to_image(&data->main_img.view, data->win.w / 2 + 1, i++, 0x000000);
	// }
	return (0);
}


void	create_wall(t_data *data,int coef_wall)
{
	int		color_wall;
	int		len_wall;
	t_point	start;
	int		curr_ray;

	color_wall = 0x0000FF;
	start.x = 0;
	len_wall = 0;
	curr_ray = data->main_img.nb_rays - 1;
	while (start.x < 640)
	{
		len_wall = data->win.h / ((data->main_img.rays[curr_ray].len));
		len_wall *= coef_wall;
		start.y = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_wall, color_wall);
		curr_ray--;
		start.x++;
		curr_ray--;
	}
	
}
void	create_floor(t_data *data,int coef_wall)
{
	int		len_wall;
	int		len_floor;
	t_point	start;
	int		curr_ray;

	start.x = 0;
	curr_ray = data->main_img.nb_rays - 1;
	while (start.x < 640)
	{
		len_wall = data->win.h / data->main_img.rays[curr_ray].len * 3;
		len_wall *= coef_wall;
		start.y = (data->win.h / 2) + (len_wall / 2);
		len_floor = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_floor,
		data->main_img.floor_color);
		start.x++;
		curr_ray--;
	}
}

void	create_sky(t_data *data,int coef_wall)
{
	int		len_wall;
	int		len_sky;
	t_point	start;
	int		curr_ray;

	start.x = 0;
	curr_ray = data->main_img.nb_rays - 1;
	while (start.x < 640)
	{
		len_wall = data->win.h / data->main_img.rays[curr_ray].len;
		start.y = 0;
		len_wall *= coef_wall;
		len_sky = (data->win.h / 2) - (len_wall / 2);
		create_vertical_line(&data->main_img.view, start, len_sky,
			data->main_img.ceilling_color);
		start.x++;
		curr_ray--;
	}
}

// int	view(t_data *data)
// {
// 	int coef_wall;

// 	coef_wall = 10;
	
// 	printf("ok");
// 	if (init_img(data, &data->main_img.view, data->win.w, data->win.h))
// 		return (-1);
// 	create_wall(data,coef_wall);
// 	create_floor(data,coef_wall);
// 	create_sky(data,coef_wall);
// 	return (0);
// }