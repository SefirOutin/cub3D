/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:56:36 by soutin            #+#    #+#             */
/*   Updated: 2024/02/25 21:31:34 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_map_header(int fd, int *error, int skip)
{
	char	*tmp;
	
	while (skip + 1)
	{
		tmp = get_next_line(fd, error);
		if (*error)
			return (-1);
		free(tmp);
		skip--;
	}
	return (0);
}

size_t	get_map_size(int fd, int *error, int *skip)
{
	char	*tmp;
	size_t	size;

	size = 0;
	while (1)
	{
		tmp = get_next_line(fd, error);
		if (*error)
			return (-1);
		if (!tmp)
			break ;
		if (!size && !ft_strncmp(tmp, "\n", 2))
			(*skip)++;
		else if (!ft_strncmp(tmp, "\n", 2))
		{
			free(tmp);
			break ;
		}
		else
			size++;
		free(tmp);
	}
	close(fd);
	return (size);
}

int	fill_colors(int *color_tab, char *tmp)
{
	int	i;
	int	j;
	int	count;
	
	i = 0;
	count = 0;
	while (count < 3 && tmp[++i])
	{
		j = i;
		while (tmp[i] && ft_isdigit(tmp[i]))
			i++;
		if (i - j == 0)
			return (1);
		if (tmp[i] && !ft_strchr(",\n", tmp[i]))
			return (1);
		tmp[i] = 0;
		color_tab[count] = ft_atoi(tmp + j);
		if (color_tab[count] < 0 || color_tab[count] > 255)
			return (1);
		count++;
	}
	if (count != 3)
		return (1);
	return (0);
}
