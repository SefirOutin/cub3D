/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/27 17:55:20 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

int	parsing(t_data *vars, char *path)
{
	ft_memset(vars, 0, sizeof(t_data));
	ft_memset(&vars->player_move, 0, sizeof(t_player));
	if (get_map_data(vars, path) < 0)
		return (1);
	if (check_map(vars))
		return (1);
	return (0);
}

void	init_img(t_data *data)
{
	int	i;

	i = 0;
	data->texture_map[0] = mlx_xpm_file_to_image(data->mlx_ptr,
													"./asset/map_asset/wall.xpm",
													&(data->size_ximg),
													&(data->size_yimg));
	data->texture_map[1] = mlx_xpm_file_to_image(data->mlx_ptr,
													"./asset/map_asset/player.xpm",
													&(data->size_ximg),
													&(data->size_yimg));
	data->texture_map[2] = mlx_xpm_file_to_image(data->mlx_ptr,
													"./asset/map_asset/floor.xpm",
													&(data->size_ximg),
													&(data->size_yimg));
	while (i < 3)
	{
		if (data->texture_map[i] == NULL)
		{
			write(2, "Error\nImage no initialise", 26);
			exit_and_free(data);
		}
		i++;
	}
}

void	erase_square(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + j, y + i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	put_square(int x, int y, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + j, y + i, 0xD35400);
			j++;
		}
		i++;
	}
}

void	dislay_player(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N')
			{
				data->pos_px = i * 50;
				data->pos_py = j * 50;
				put_square(data->pos_px, data->pos_py, data);
			}
			i++;
		}
		j++;
	}
}

void	display_map_2(t_data *data, int *i, int *j)
{
	if (data->map[*j][*i] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->texture_map[0], (*i * 50), (*j * 50));
	if (data->map[*j][*i] == '0' || data->map[*j][*i] == 'N')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->texture_map[2], (*i * 50), (*j * 50));
}

void	display_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			display_map_2(data, &i, &j);
			i++;
		}
		i = 0;
		j++;
	}
}

void	move(t_data *data, double x, double y)
{
	erase_square(data, data->pos_px, data->pos_py);
	data->pos_px += x;
	data->pos_py += y;
	put_square(data->pos_px, data->pos_py, data);
	return ;
}

void	print_int_tab(int tab[6][2], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("i:%d ::::  %d\n", i, tab[i][1]);
		i++;
	}
}

int	on_keypress(t_data *data)
{
	int	i;

	i = 0;
	while (i < 100000)
		i++;
	if (data->player_move.forward == 1)
		move(data, 0, -0.005);
	if (data->player_move.backward == 1)
		move(data, 0,0.005);
	if (data->player_move.left == 1)
		move(data, -0.005, 0);
	if (data->player_move.right == 1)
		move(data, 0.005, 0);
	return (0);
}

int	release_inputs(int keysym, t_data *data)
{
	if (keysym == 119 && data->player_move.forward == 1)
		data->player_move.forward = 0;
	if (keysym == 115 && data->player_move.backward == 1)
		data->player_move.backward = 0;
	if (keysym == 97 && data->player_move.left == 1)
		data->player_move.left = 0;
	if (keysym == 100 && data->player_move.right == 1)
		data->player_move.right = 0;
	if (keysym == 65361 && data->player_move.rotate == 1)
		data->player_move.rotate = 0;
	if (keysym == 65363 && data->player_move.rotate == 1)
		data->player_move.rotate = 0;
	return (0);
}

int	get_inputs(int keysym, t_data *data)
{
	printf("key :%d\n", keysym);
	if (keysym == 65307)
		exit_and_free(data);
	if (keysym == 119)
		data->player_move.forward = 1;
	if (keysym == 115)
		data->player_move.backward = 1;
	if (keysym == 97)
		data->player_move.left = 1;
	if (keysym == 100)
		data->player_move.right = 1;
	if (keysym == 65361)
		data->player_move.rotate= 1;
	if (keysym == 65363)
		data->player_move.rotate = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argv[1]))
		return (1);
	data.size_ximg = 50;
	data.size_yimg = 50;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.x_max * 50,
			ft_arraylen(data.map) * 50, "MazeCub3D");
	if (!data.win_ptr)
		return (free(data.win_ptr), -1);
	init_img(&data);
	display_map(&data);
	dislay_player(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, release_inputs, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, get_inputs, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
			&data);
	mlx_loop_hook(data.mlx_ptr, on_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
