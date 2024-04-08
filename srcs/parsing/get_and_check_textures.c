/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_check_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:51:46 by soutin            #+#    #+#             */
/*   Updated: 2024/04/08 20:43:02 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_textures_data3(t_data *data, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("C ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(&data->main.ceilling_color, tmp + g_s_color(tmp + 1)))
			return (print_err("invalid color"), -1);
	}
	else if (!ft_strncmp(tmp, "\n", 2))
		return (0);
	else
		return (print_err("header"), -1);
	return (0);
}

int	fill_textures_data2(t_data *data, char *tmp, int *nb_textures)
{
	if (!data->main.textures_path[2] && !ft_strncmp("SO ", tmp, 3)
		&& ++(*nb_textures))
	{
		data->main.textures_path[2] = ft_substr(tmp, g_s(tmp + 2),
				ft_strlen(tmp + g_s(tmp + 2)) - 1);
		if (!data->main.textures_path[2])
			return (-1);
	}
	else if (!data->main.textures_path[3] && !ft_strncmp("WE ", tmp, 3)
		&& ++(*nb_textures))
	{
		data->main.textures_path[3] = ft_substr(tmp, g_s(tmp + 2),
				ft_strlen(tmp + g_s(tmp + 2)) - 1);
		if (!data->main.textures_path[3])
			return (-1);
	}
	else if (!ft_strncmp("F ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(&data->main.floor_color, tmp + g_s_color(tmp + 1)))
			return (print_err("invalid color"), -1);
	}
	else if (fill_textures_data3(data, tmp, nb_textures) < 0)
		return (-1);
	return (0);
}

int	fill_textures_data(t_data *data, char *tmp, int *nb_textures)
{
	if (!data->main.textures_path[0] && !ft_strncmp("NO ", tmp, 3)
		&& ++(*nb_textures))
	{
		data->main.textures_path[0] = ft_substr(tmp, g_s(tmp + 2),
				ft_strlen(tmp + g_s(tmp + 2)) - 1);
		if (!data->main.textures_path[0])
			return (-1);
	}
	else if (!data->main.textures_path[1] && !ft_strncmp("EA ", tmp, 3)
		&& ++(*nb_textures))
	{
		data->main.textures_path[1] = ft_substr(tmp, g_s(tmp + 2),
				ft_strlen(tmp + g_s(tmp + 2)) - 1);
		if (!data->main.textures_path[1])
			return (-1);
	}
	else if (fill_textures_data2(data, tmp, nb_textures) < 0)
		return (-1);
	return (0);
}
