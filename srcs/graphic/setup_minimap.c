#include "cub3d.h"

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < MINI_W && y < MINI_H)
	{
		dst = (char *)img.addr + (y * img.line_l + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)(((char *)img.addr + (y * img.line_l) + (x
					* img.bpp / 8))));
}

void	put_img_to_img(t_img dst, t_img src, int x, int y, int width,
		int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

void	init_asset(t_img *asset, t_data *data)
{
	asset[0].img = mlx_new_image(data->mlx_ptr, 15, 15);
	asset[1].img = mlx_new_image(data->mlx_ptr, 15, 15);
	asset[2].img = mlx_new_image(data->mlx_ptr, 15, 15);
	asset[0].addr = (int *)mlx_get_data_addr(data->mnmap.textures[3],
			&(asset[0].bpp), &(asset[0].line_l), &(asset[0].endian));
	asset[1].addr = (int *)mlx_get_data_addr(data->mnmap.textures[4],
			&(asset[1].bpp), &(asset[1].line_l), &(asset[1].endian));
	asset[2].addr = (int *)mlx_get_data_addr(data->mnmap.textures[5],
			&(asset[2].bpp), &(asset[2].line_l), &(asset[2].endian));
}

void	create_minimap_window(t_img *win_minimap, t_data *data)
{
	win_minimap->img = mlx_new_image(data->mlx_ptr, MINI_W, MINI_H);
	win_minimap->addr = (int *)mlx_get_data_addr(win_minimap->img,
			&(win_minimap->bpp), &(win_minimap->line_l),
			&(win_minimap->endian));
}
void	print_minimap(t_img *win_minimap, t_data *data, t_img *asset)
{
	int	i;
	int	j;
	int	player_x;
	int	player_y;
	int	x;
	int	y;

	player_x = data->player_mini.px;
	player_y = data->player_mini.py;
	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			x = (i * 15) - (player_x - MINI_H / 2);
			y = (j * 15) - (player_y - MINI_W / 2); // Inversion de l'axe y
			if (ft_strchr("1", data->map[j][i]))
				put_img_to_img(*win_minimap, asset[0], x, y, 15, 15);
			if (ft_strchr("0NSWE", data->map[j][i]))
				put_img_to_img(*win_minimap, asset[1], x, y, 15, 15);
			i++;
		}
		j++;
	}
}
void	draw_mini_xpm(t_data *data, t_img *img, double angle)
{
	int	color;
	int	x;
	int	y;
	int	new_x;
	int	new_y;

	y = 0;
	while (y < 15)
	{
		x = 0;
		while (x < 15)
		{
			new_x = round((x - 7.5) * cos(angle) - (y - 7.5) * sin(angle)
					+ 7.5);
			new_y = round((x - 7.5) * sin(angle) - (y - 7.5) * cos(angle)
					+ 7.5);
			color = data->asset[2].addr[y * 15 + x];
			if (color >= 0 && new_x >= 0 && new_x < 15 && new_y >= 0
				&& new_y < 15)
				put_pixel_img(*img, new_x + (MINI_W / 2) - 7.5 , new_y + (MINI_H / 2)- 7.5, color);
			x++;
		}
		y++;
	}
}




void	destroy_image(t_img img, t_data *data)
{
	if (img.img)
		mlx_destroy_image(data->mlx_ptr, img.img);
}

void	setup_minimap(t_data *data)
{
	t_img window_minimap;

	create_minimap_window(&window_minimap, data);
	print_minimap(&window_minimap, data, data->asset);
	draw_mini_xpm(data, &window_minimap,
	deg_to_rad(fix_ang(data->player.direction +90 )));
	// mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,window_minimap.img,0,0);
	put_img_to_img(data->view, window_minimap, 10, 10, MINI_W, MINI_H);
	destroy_image(window_minimap, data);
}