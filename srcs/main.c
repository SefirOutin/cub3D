/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/21 19:16:17 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int fill_map(t_vars *vars, char *path, size_t size, int skip)
{
    char	*tmp;
	int		fd;
	int		i;
	int		error;

	i = 0;
	error = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	vars->map = ft_calloc(size + 1, sizeof(char *));
	if (!vars->map)
		return (-1);
	while (skip)
	{
		tmp = get_next_line(fd, &error);
		if (error)
			return (-1);
		free(tmp);
		skip--;
	}
	while (i < size)
	{
		tmp = get_next_line(fd, &error);
		if (error)
			return (-1);
		vars->map[i] = ft_strdup(tmp);
		if (!vars->map[i])
			return (-1);
		i++;
	}
	vars->map[i] = NULL;
	return (0);
}

int parse(t_vars *vars, char *path)
{
    int     fd;
    char    *tmp;
    int     nb_textures;
    size_t	size;
	int		error;
	int		skip;

    size = 0;
	skip = 0;
	nb_textures = 0;
	error = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (-1);
    while (1)
    {
        tmp = get_next_line(fd, &error);
        if (error)
            return (-1);
		if (!tmp)
			break ;
        if (!ft_strncmp("NO ", tmp, 3))
		{
			vars->north_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
			nb_textures++;
		}
        else if (!ft_strncmp("SO ", tmp, 3))
		{
			vars->south_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
			nb_textures++;	
		}
        else if (!ft_strncmp("WE ", tmp, 3))
		{
			vars->west_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
			nb_textures++;
		}
        else if (!ft_strncmp("EA ", tmp, 3))
		{
			vars->east_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
			nb_textures++;
		}
        else if (!ft_strncmp("F ", tmp, 2))
		{
			vars->floor_color = ft_substr(tmp, 2, ft_strlen(tmp + 2));
			nb_textures++;
		}
        else if (!ft_strncmp("C ", tmp, 2))
		{
			vars->ceilling_color = ft_substr(tmp, 2, ft_strlen(tmp + 2));
			nb_textures++;
		}
		skip++;
		free(tmp);
		if (nb_textures == 6)
			break ;
    }
    while (1)
    {
        tmp = get_next_line(fd, &error);
        if (error)
            return (-1);
		if (!tmp)
			break ;
        free(tmp);
        size++;
    }
    close(fd);
    fill_map(vars, path, size, skip);
	ft_print_tab(vars->map);
	return (0);
}
int	main_graphic(int argc, char **argv)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, ft_strlen(data.map[0]) * 50,
			ft_arraylen(data.map) * 50, "MazeCub3D");
    if(!data.win_ptr)
        return (free(data.win_ptr),-1);
    init_img(data);
    display_map(data);
    mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
		&data);
	mlx_loop(data.mlx_ptr);
}
