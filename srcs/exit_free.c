/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:08 by soutin            #+#    #+#             */
/*   Updated: 2024/03/15 18:26:21 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_section(t_point **section, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(section[i]);
		i++;
	}
}

int	exit_and_free(t_data *data)
{
	// int i;

	// i = 0;
	ft_free_tab(data->map);
	// free(data->textures[0]);
	// free(data->textures[1]);
	// free(data->textures[2]);
	// free(data->textures[3]);
	if (data->win.win_ptr)
		mlx_destroy_window(data->win.mlx_ptr, data->win.win_ptr);
	if (data->win.mlx_ptr)
	{
		mlx_destroy_display(data->win.mlx_ptr);
		free(data->win.mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}