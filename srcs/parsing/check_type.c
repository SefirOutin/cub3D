/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:09:01 by bmoudach          #+#    #+#             */
/*   Updated: 2024/03/31 19:09:07 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_type(char *path, char *type)
{
	int	i;
	int	size;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
		{
			size = ft_strlen(path + i);
			if (size < ft_strlen(type))
				size = ft_strlen(type);
			return (ft_strncmp(path + i + 1, type, size));
		}
		i++;
	}
	return (1);
}
