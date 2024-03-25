/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:08 by soutin            #+#    #+#             */
/*   Updated: 2024/03/23 16:22:05 by bmoudach         ###   ########.fr       */
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
	ft_free_tab(data->map);
	if (data->win.win_ptr)
		mlx_destroy_window(data->win.mlx_ptr, data->win.win_ptr);
	if (data->win.mlx_ptr)
	{
		mlx_destroy_display(data->win.mlx_ptr);
		free(data->win.mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}