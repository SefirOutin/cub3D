/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/27 19:01:39 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	print_err(char *err_message)
{
	ft_printf("Error\n%s\n", err_message);
}

void	move(t_data *data, int x, int y)
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
