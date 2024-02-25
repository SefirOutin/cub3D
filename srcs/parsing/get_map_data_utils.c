/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:56:36 by soutin            #+#    #+#             */
/*   Updated: 2024/02/25 15:57:01 by soutin           ###   ########.fr       */
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

size_t	get_map_size(int fd, int *error, int *skip)
{
	char *tmp;
	size_t size;

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
		else
			size++;
		free(tmp);
	}
	close(fd);
	return (size);
}