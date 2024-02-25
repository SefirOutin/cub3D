/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:52:16 by soutin            #+#    #+#             */
/*   Updated: 2024/02/25 21:22:20 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_data(t_vars *vars, char *path)
{
	int		fd;
	int		error;
	int		skip;
	size_t	size;

	error = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	skip = get_textures(vars, fd, &error);
	if (skip < 0)
		return (-1);
	size = get_map_size(fd, &error, &skip);
	if (size < 0)
		return (-1);
	vars->map = ft_calloc(size + 1, sizeof(char *));
	if (!vars->map)
		return (-1);
	if (fill_map(vars, path, size, skip) < 0)
		return (-1);
	ft_print_tab(vars->map);
	return (0);
}

int	get_textures(t_vars *vars, int fd, int *error)
{
	int		nb_textures;
	char	*tmp;
	int		skip;

	nb_textures = 0;
	skip = 0;
	while (nb_textures != 6)
	{
		tmp = get_next_line(fd, error);
		if (*error)
			return (-1);
		if (!tmp)
			break ;
		if (fill_textures_vars(vars, tmp, &nb_textures) < 0)
			return (free(tmp), -1);
		free(tmp);
		skip++;
	}
	if (nb_textures != 6)
		return (-1);
	return (skip);
}

int	fill_textures_vars2(t_vars *vars, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("EA ", tmp, 3) && ++(*nb_textures))
	{
		vars->east_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->east_texture)
			return (-1);
	}
	else if (!ft_strncmp("F ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(vars->floor_color, tmp + 1))
			return (printf("error: invalid color\n"), -1);
	}
	else if (!ft_strncmp("C ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(vars->ceilling_color, tmp + 1))
			return (printf("error: invalid color\n"), -1);
	}
	else if (!ft_strncmp(tmp, "\n", 2))
		return (0);
	else
		return (1);
	return (0);
}

int	fill_textures_vars(t_vars *vars, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("NO ", tmp, 3) && ++(*nb_textures))
	{
		vars->north_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->north_texture)
			return (-1);
	}
	else if (!ft_strncmp("SO ", tmp, 3) && ++(*nb_textures))
	{
		vars->south_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->south_texture)
			return (-1);
	}
	else if (!ft_strncmp("WE ", tmp, 3) && ++(*nb_textures))
	{
		vars->west_texture = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->west_texture)
			return (-1);
	}
	else if (fill_textures_vars2(vars, tmp, nb_textures) < 0)
		return (-1);
	return (0);
}

int	fill_map(t_vars *vars, char *path, size_t size, int skip)
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
	if (skip_map_header(fd, &error, skip) < 0)
		return (-1);
	while (i < size)
	{
		tmp = get_next_line(fd, &error);
		if (error)
			return (-1);
		if (!ft_strncmp(tmp, "\n", 2))
		{
			free(tmp);
			break ;	
		}
		vars->map[i] = ft_strdup(tmp);
		if (!vars->map[i])
			return (free(tmp), -1);
		if (vars->map[i][ft_strlen(tmp) - 1] == '\n')
			vars->map[i][ft_strlen(tmp) - 1] = 0;
		i++;
		free(tmp);
	}
	return (vars->map[i] = NULL, close(fd), 0);
}
