/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:59 by bmoudach          #+#    #+#             */
/*   Updated: 2024/04/08 15:40:54 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_same(char **array)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!array[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_path_img(char **array)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < 4)
	{
		if (array[i] && check_type(array[i], "xpm"))
		{
			fd = open(array[i], O_RDONLY);
			if (fd < 0)
				return (free_static_tab(array), print_err("Bad path img"),
					1);
			close(fd);
		}
		i++;
	}
	if (check_if_same(array))
		return (free_static_tab(array), print_err("Double key"), 1);
	return (0);
}
