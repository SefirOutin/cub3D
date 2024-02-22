/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/22 20:10:16 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	main_graphic(int argc, char **argv)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, ft_strlen(data.map[0]) * 50,
			ft_arraylen(data.map) * 50, "MazeCub3D");
    if(!data.win_ptr)
        return (free(data.win_ptr),-1);
    init_img(data);
    display_map(data);
    mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
		&data);
	mlx_loop(data.mlx_ptr);
}
