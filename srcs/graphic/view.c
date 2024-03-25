/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:28:04 by soutin            #+#    #+#             */
/*   Updated: 2024/03/25 18:56:41 by soutin           ###   ########.fr       */
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

void	put_vertical_line_img_to_img(t_img *dst, t_img src, int x, int offset, int y, int height)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		put_pixel_img(dst, x, y + i, get_pixel_img(src, offset,i));
		i++;
		j--;
	}
}

void	draw_wall(t_data *data, int x, int ys[2], int ratio, int curr_ray)
{
	int	half_height;
	int	wall_height;
	int offset_x;
	int	offset_y;
	int	start_y;
	
	half_height = data->win.h * 0.5;
	wall_height = data->win.h / (data->main.rays[curr_ray].len * 1.5);
	if (curr_ray == 45)
		printf("wall :%d\n", wall_height);
	ys[0] = half_height + wall_height / 2;
	ys[1] = half_height - wall_height / 2;
	start_y = (data->win.h / 2) - (wall_height / 2);
	offset_x = (data->main.rays[curr_ray].end.x - (int)data->main.rays[curr_ray].end.x) * 100;
	offset_y = (data->main.rays[curr_ray].end.y - (int)data->main.rays[curr_ray].end.y) * 100;
	
	// printf("start y:%f xxX:%d\n", data->main.rays[curr_ray].end.x, offset_x);
	put_vertical_line_img_to_img(&data->main.view, data->main.textures[0], x, offset_x, start_y, wall_height);	
	
	// mlx_pixel_put(data->win.mlx_ptr, data->win.win_ptr, x, start_y, 0x7FFF00);
}

void	draw_ceil_and_floor(t_data *data, int x, int ys[2], int ratio)
{
	int	i;
	
	while (ys[0] < data->win.h)
	{
		i = 0;
		while (i < ratio)
		{
			put_pixel_to_image(&data->main.view, x + i, ys[0],
				data->main.floor_color);
			put_pixel_to_image(&data->main.view, x + i++, ys[1],
				data->main.ceilling_color);
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
	ratio = data->win.w / data->main.nb_rays;
	// printf("nb %d\n", data->main.nb_rays);
	curr_ray = data->main.nb_rays - 1;
	if (init_img(data, &data->main.view, data->win.w, data->win.h))
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
	// 	put_pixel_to_image(&data->main.view, data->win.w / 2 - 1, i, 0x000000);
	// 	put_pixel_to_image(&data->main.view, data->win.w / 2, i, 0x000000);
	// 	put_pixel_to_image(&data->main.view, data->win.w / 2 + 1, i++, 0x000000);
	// }
	free(data->main.rays);
	return (0);
}


