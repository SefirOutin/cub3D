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

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
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
void print_minimap(t_img *win_minimap, t_data *data, t_img *asset)
{
    int i;
    int j;
    int player_x = data->player_mini.px;
    int player_y = data->player_mini.py;
    int half_mini_width = MINI_W / 2;  // Taille de la minimap divisée par 2 et par la taille des tuiles
    int half_mini_height = MINI_H / 2; // Taille de la minimap divisée par 2 et par la taille des tuiles
    int x;
    int y;

    j = 0;
    while (data->map[j])
    {
        i = 0;
        while (data->map[j][i])
        {
            x = (i * 15) - (player_x - half_mini_width);
            y = (j * 15) - (player_y + half_mini_height); // Inversion de l'axe y
            
            if (ft_strchr("1", data->map[j][i]))
                put_img_to_img(*win_minimap, asset[0], x, y);
            if (ft_strchr("0NSWE", data->map[j][i]))
                put_img_to_img(*win_minimap, asset[1], x, y);
            // if (ft_strchr("NSWE", data->map[j][i]))
            //     put_img_to_img(*win_minimap, asset[2], x, y);
            i++;
        }
        j++;
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
	put_img_to_img(data->view,window_minimap,0,0);
	// destroy_image(window_minimap, data);
}