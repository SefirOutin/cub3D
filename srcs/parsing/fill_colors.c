/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:55:43 by bmoudach          #+#    #+#             */
/*   Updated: 2024/04/12 15:04:05 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	check_format_rgb(char *rgb)
{
	int	i;
	int	nb_cma;
	int	nb_per_part[3];

	i = 0;
	nb_cma = 0;
	ft_bzero(nb_per_part, sizeof(nb_per_part));
	while (rgb[i] && rgb[i] != '\n')
	{
		if (ft_isdigit(rgb[i]))
			nb_per_part[nb_cma]++;
		else if ((rgb[i] == ',' && ++nb_cma) || rgb[i] == ' ' || rgb[i] == '\t')
			;
		else
			return (1);
		i++;
	}
	if (nb_cma != 2 || nb_per_part[0] < 1 || nb_per_part[1] < 1
		|| nb_per_part[2] < 1)
		return (1);
	return (0);
}

void	del_char(char *address, char char_to_del)
{
	while (*address != '\0' && *address != char_to_del)
		address++;
	if (*address == char_to_del)
	{
		while (*address != '\0')
		{
			*address = *(address + 1);
			address++;
		}
	}
}

int	err_spc_rgbpart(char *rgb_part)
{
	int	i;

	i = 0;
	while (rgb_part[i] == ' ' || rgb_part[i] == '\t')
		i++;
	while (ft_isdigit(rgb_part[i]))
		i++;
	while (rgb_part[i] == ' ' || rgb_part[i] == '\t')
		i++;
	if (rgb_part[i] && rgb_part[i] != '\n')
		return (1);
	return (0);
}

int	fill_colors(int *color, char *tmp)
{
	int		colors[3];
	int		i;
	char	**colors_split;

	i = -1;
	if (check_format_rgb(tmp))
		return (1);
	colors_split = ft_split(tmp, ',');
	if (!colors_split)
		return (1);
	if (ft_arraylen(colors_split) > 3)
		return (ft_free_tab(colors_split), 1);
	while (++i < 3)
	{
		colors[i] = ft_atoi(colors_split[i]);
		if (err_spc_rgbpart(colors_split[i]))
			return (ft_free_tab(colors_split), 1);
		if (colors[i] < 0 || colors[i] > 255)
			return (ft_free_tab(colors_split), 1);
	}
	ft_free_tab(colors_split);
	return (*color = create_rgb(colors[0], colors[1], colors[2]), 0);
}
