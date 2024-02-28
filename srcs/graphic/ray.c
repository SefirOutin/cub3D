#include "cub3d.h"
#include <stdio.h>

// int	put_vector(t_data *data, int x, int y, int rotate)
// {
// 	int	
// }

int	put_ray(t_data *data)
{
	int	i;
	int	y;
	int	save;
	int	count;

	i = 0;
	while (1)
	{

		y = (data->player.py - 3 - i) / 50;
		save = data->map[y][(int)(data->player.px / 50)];
		printf("save:%c\n", save);
		count = (data->player.py - i) - (((int)(data->player.py- i) / 50) * 50);
		printf("count : %d\n", count);
		if (save == '1')
			break ;
		while (count > -1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->player.px, (int)data->player.py - i - count,
				0x7FFF00);
			count--;
		}
		i++;
	}
	return (0);
}

int	erased_ray(t_data *data)
{
	int	i;
	int	y;
	int	save;
	int	count;

	i = 0;
	while (1)
	{
		y = (data->player.py - 3 - i) / 50;
		save = data->map[y][(int)(data->player.px / 50)];
		printf("save:%c\n", save);
		count = (data->player.py - i) - (((int)(data->player.py- i) / 50) * 50);
		printf("count : %d\n", count);
		if (save == '1')
			break ;
		while (count > -1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->player.px, (int)data->player.py - i - count,
				0xFFFFFF);
			count--;
		}
		i++;
	}
	return (0);
}