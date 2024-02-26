/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/22 20:15:55 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

int	parsing(t_vars *vars, char *path)
{
	ft_memset(vars, 0, sizeof(t_vars));
	if (get_map_data(vars, path) < 0)
		return (1);
	if (check_map(vars))
		return (1);
	ft_print_tab(vars->map);
	return (0);
}

void	init_img(t_data *data)
{
	int	i;

	i = 0;
	data->texture[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/wall.xpm", &(data->size_ximg),
			&(data->size_yimg));
	data->texture[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/player.xpm", &(data->size_ximg),
			&(data->size_yimg));
	data->texture[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./asset/map_asset/floor.xpm", &(data->size_ximg),
			&(data->size_yimg));
	while (i < 3)
	{
		if (data->texture[i] == NULL)
		{
			write(2, "Error\nImage no initialise", 26);
			exit_and_free(data);
		}
		i++;
	}
}
void	display_map_2(t_data *data, int *i, int *j)
{
	if (data->map[*j][*i] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture[0],
			(*i * 50), (*j * 50));
	if (data->map[*j][*i] == '0' || data->map[*j][*i] == 'N')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture[2],
			(*i * 50), (*j * 50));
	if (data->map[*j][*i] == 'N')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture[1],
			(*i * 50), (*j * 50));
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

void	move(t_data *data, int x, int y)
{
	return ;
}
int	on_keypress(int keysym, t_data *data)
{
	if (keysym == 65307)
		exit_and_free(data);
	if (keysym == 119 || keysym == 65362)
		move(data, 0, -1);
	if (keysym == 115 || keysym == 65364)
		move(data, 0, 1);
	if (keysym == 97 || keysym == 65361)
		move(data, -1, 0);
	if (keysym == 100 || keysym == 65363)
		move(data, 1, 0);
	return (0);
}
int	main(int argc, char **argv)
{
	t_data	data;
	t_vars	data1;

	parse(&data1, argv[1]);
	data.map = data1.map;
	data.size_ximg = 50;
	data.size_yimg = 50;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, ft_strlen(data.map[0]) * 50,
			ft_arraylen(data.map) * 50, "MazeCub3D");
	if (!data.win_ptr)
		return (free(data.win_ptr), -1);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	init_img(&data);
	display_map(&data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
