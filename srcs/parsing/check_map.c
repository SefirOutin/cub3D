/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:39:40 by soutin            #+#    #+#             */
/*   Updated: 2024/02/25 21:29:27 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int tab_size(char **tab)
{
    int i;
    
    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int prout(char **map, int x, int y)
{
	int	player;
	
	player = 0;
    if (!x || x == ft_strlen(map[y]) - 1)
    {
		if (ft_strchr("0NSWE", map[y][x]))
        	return (1);
	}
    else if (map[y][x] == '0'
			&& ((map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
			|| (x > ft_strlen(map[y - 1]) - 1 || x > ft_strlen(map[y + 1]) - 1)
			|| (x <= ft_strlen(map[y - 1]) - 1 && map[y - 1][x] == ' ')
			|| (x <= ft_strlen(map[y + 1]) - 1 && map[y + 1][x] == ' ')))
			return (1);
	// else if (map[y][x] == '0' && (map[y][x + 1] == ' ' || map[y][x - 1] == ' '))
	//     return (1);
    // else if (map[y][x] == '0' && (x > ft_strlen(map[y - 1]) - 1 || x > ft_strlen(map[y + 1]) - 1))
	// 	return (1);
	// else if (map[y][x] == '0' && (x <= ft_strlen(map[y - 1]) - 1 && map[y - 1][x] == ' '))
	// 	return (1);
	// else if (map[y][x] == '0' && (x <= ft_strlen(map[y + 1]) - 1 && map[y + 1][x] == ' '))
	// 	return (1);
	return (0);
}

int check_map(t_vars *vars)
{
    int x;
    int y;

    y = 0;
    while (vars->map[y])
    {
        x = 0;
        while (vars->map[y][x])
        {
            if (!ft_strchr("01NSEW\n ", vars->map[y][x]))
                return (printf("error: invalid character\n"), 1);
            if (!y || y == tab_size(vars->map) - 1)
            {
                if (!ft_strchr(" 1\n", vars->map[y][x]))
                    return (printf("error: unclosed map\n"), 1);
            }
            else if (prout(vars->map, x, y))
                return (printf("error: unclosed map\n"), 1);
            x++;
        }
        y++;
    }
    return (0);
}
