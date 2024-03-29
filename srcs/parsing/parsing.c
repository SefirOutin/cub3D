/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:57:21 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 18:37:41 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	find_player(t_data *data);

int	parsing(t_data *data, char *path)
{
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(&data->player, 0, sizeof(t_player));
	if (get_map_data(data, path) < 0)
		return (1);
	if (check_map(data))
		return (1);
	find_player(data);
	return (0);
}

int	check_char(char **map, int y, int x)
{
	if (!ft_strchr("01NSEW ", map[y][x]))
		return (print_err("forbidden character"), 1);
	if (!y || y == ft_arraylen(map) - 1)
	{
		if (!ft_strchr(" 1", map[y][x]))
			return (print_err("unclosed map"), printf("x:%d y:%d", x, y), 1);
	}
	else if (!x || x == ft_strlen(map[y]) - 1)
	{
		if (ft_strchr("0NSWE", map[y][x]))
			return (print_err("unclosed map"), printf("x:%d y:%d", x, y), 1);
	}
	else if (ft_strchr("0NSWE", map[y][x])
			&& ((map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
			|| (x > ft_strlen(map[y - 1]) - 1 || x > ft_strlen(map[y + 1]) - 1)
			|| (x <= ft_strlen(map[y - 1]) - 1 && map[y - 1][x] == ' ')
			|| (x <= ft_strlen(map[y + 1]) - 1 && map[y + 1][x] == ' ')))
		return (print_err("unclosed map"), printf("x:%d y:%d", x, y), 1);
	return (0);
}

int	check_map(t_data *vars)
{
	int	x;
	int	y;
	int	player;

	y = 0;
	player = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			if (check_char(vars->map, y, x))
				return (1);
			if (ft_strchr("NSWE", vars->map[y][x]))
				player++;
			x++;
		}
		if (x > vars->minimap.w)
			vars->minimap.w = x;
		y++;
	}
	if (player != 1)
		return (print_err("number of player"), 1);
	vars->minimap.h = y;
	return (0);
}

char	*dup_line(char *tmp)
{
	char	*str;

	str = ft_strdup(tmp);
	if (!str)
		return (free(tmp), NULL);
	if (str[ft_strlen(tmp) - 1] == '\n')
		str[ft_strlen(tmp) - 1] = 0;
	return (str);
}
