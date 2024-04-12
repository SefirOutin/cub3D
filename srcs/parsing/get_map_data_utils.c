/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:56:36 by soutin            #+#    #+#             */
/*   Updated: 2024/04/12 09:17:21 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_map_header(int fd, int *error, int skip)
{
	char	*tmp;

	while (skip)
	{
		tmp = get_next_line(fd, error);
		if (*error)
			return (-1);
		free(tmp);
		skip--;
	}
	return (0);
}

long	get_map_size_and_check_is_last(int fd, int *error, int *skip)
{
	long	size;
	char	*tmp;

	size = get_map_size(fd, error, skip);
	if (!size)
		return (print_err("missing map"), -1);
	while (1)
	{
		tmp = get_next_line(fd, error);
		if (*error)
			return (-1);
		if (!tmp)
			return (free(tmp), close(fd), size);
		if (ft_strncmp(tmp, "\n", 2))
		{
			free(tmp);
			return (print_err("something after the map"), -1);
		}
		free(tmp);
	}
}

long	get_map_size(int fd, int *error, int *skip)
{
	char	*tmp;
	long	size;

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
			return (free(tmp), size);
		else
			size++;
		free(tmp);
	}
	return (size);
}
