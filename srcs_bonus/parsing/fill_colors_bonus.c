/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:17:41 by bmoudach          #+#    #+#             */
/*   Updated: 2024/04/12 09:17:43 by bmoudach         ###   ########.fr       */
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

	i = 0;
	nb_cma = 0;
	while (rgb[i] != '\n')
	{
		if (ft_isdigit(rgb[i]))
			i++;
		else if (rgb[i] == ',' || rgb[i] == ' ')
		{
			if (rgb[i] == ',')
				nb_cma++;
			i++;
		}
		else
			return (1);
	}
	if (nb_cma != 2)
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
		del_char((char *)colors_split[i], ' ');
		colors[i] = ft_atoi(colors_split[i]);
		if (colors[i] < 0 || colors[i] > 255)
			return (ft_free_tab(colors_split), 1);
	}
	ft_free_tab(colors_split);
	return (*color = create_rgb(colors[0], colors[1], colors[2]), 0);
}
