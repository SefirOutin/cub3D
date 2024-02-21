/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/21 23:56:12 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse(t_vars *vars, char *path)
{
    int     fd;
    char    *tmp;
    int     nb_textures;

	nb_textures = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (-1);
    while (1)
    {
        tmp = get_next_line(fd);
        if (!tmp)
            return (-1);
        if (!ft_strncmp("NO ", tmp, 3))
			vars->north_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
        else if (!ft_strncmp("SO ", tmp, 3))
			vars->south_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
        else if (!ft_strncmp("WE ", tmp, 3))
			vars->west_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
        else if (!ft_strncmp("EA ", tmp, 3))
			vars->east_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
        else if (!ft_strncmp("F ", tmp, 2))
			vars->floor_color = ft_substr(tmp, 2, ft_strlen(tmp + 2));
        else if (!ft_strncmp("C ", tmp, 2))
			vars->ceilling_color = ft_substr(tmp, 2, ft_strlen(tmp + 2));
		nb_textures++;
		free(tmp);
		if (nb_textures == 6)
			break ;
    }
	return (0);
}

int main(int c, char **v)
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(t_vars));
    if (c == 2)
    {
        parse(&vars, v[1]);
    }
	printf("%s\n", vars.north_texture);
    // else
    //     printf("invalid args\n");
}