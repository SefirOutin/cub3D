#include "cub3d.h"
#include <stdio.h>

int	put_ray(t_data *data)
{
	int	i;
	int	x;

	x = data->pos_px + 4;
	i = 0;
	while (i < 20000)
	{
		if (data->map[(int)(((data->pos_py - i) + 1)/ 50) ][(x + 1) / 50] == '1')
			return (0);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, (int)data->pos_py - 1,
			0x7FFF00);
		if (data->map[(int)((((int)data->pos_py - i) + 1)/ 50) ][(x + 1 + 1)/ 50] == '1')
			return (0);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + 1, (int)data->pos_py
			- i, 0x7FFF00);
		if (data->map[(int)((((int)data->pos_py - i) +1 )/ 50)][(x + 2 + 1)/ 50 ] == '1')
			return (0);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + 2, (int)data->pos_py
			- i, 0x7FFF00);
		i++;
	}
	return (0);
}

int	erased_ray(t_data *data)
{
	int i;
	int x;

	x = data->pos_px + 4;
	i = 0;
	while (i < 20000)
	{
		if (data->map[(int)(((data->pos_py - i) + 1)/ 50) ][(x + 1) / 50] == '1')
			return (0);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, (int)data->pos_py - 1,
			0xFFFFFF);
		if (data->map[(int)((((int)data->pos_py - i) + 1)/ 50) ][(x + 1 + 1)/ 50] == '1')
			return (0);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + 1, (int)data->pos_py
			- i, 0xFFFFFF);
		if (data->map[(int)((((int)data->pos_py - i) +1 )/ 50)][(x + 2 + 1)/ 50 ] == '1')
			return (0);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + 2, (int)data->pos_py
			- i, 0xFFFFFF);
		i++;
		i++;
	}
	return (0);
}