/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:52:16 by soutin            #+#    #+#             */
/*   Updated: 2024/02/26 18:15:55 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_data(t_data *vars, char *path)
{
	int		fd;
	int		error;
	int		skip;
	long	size;

	error = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n"), perror("map file"), -1);
	skip = get_textures(vars, fd, &error);
	if (skip < 0)
		return (-1);
	size = get_map_size_and_check_is_last(fd, &error, &skip);
	if (size < 0)
		return (-1);
	vars->map = ft_calloc(size + 1, sizeof(char *));
	if (!vars->map)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n"), perror("map file"), -1);
	if (fill_map(vars, fd, size, skip) < 0)
		return (-1);
	return (0);
}

int	get_textures(t_data *vars, int fd, int *error)
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
		return (print_err("missing information"), -1);
	vars->textures[4] = NULL;
	return (skip);
}

int	fill_textures_vars2(t_data *vars, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("WE ", tmp, 3) && ++(*nb_textures))
	{
		vars->textures[3] = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->textures[3])
			return (-1);
	}
	else if (!ft_strncmp("F ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(vars->floor_color, tmp + 1))
			return (print_err("invalid color"), -1);
	}
	else if (!ft_strncmp("C ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(vars->ceilling_color, tmp + 1))
			return (print_err("invalid color"), -1);
	}
	else if (!ft_strncmp(tmp, "\n", 2))
		return (0);
	else
		return (print_err("header"), -1);
	return (0);
}

int	fill_textures_vars(t_data *vars, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("NO ", tmp, 3) && ++(*nb_textures))
	{
		vars->textures[0] = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->textures[0])
			return (-1);
	}
	else if (!ft_strncmp("EA ", tmp, 3) && ++(*nb_textures))
	{
		vars->textures[1] = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->textures[1])
			return (-1);
	}
	else if (!ft_strncmp("SO ", tmp, 3) && ++(*nb_textures))
	{
		vars->textures[2] = ft_substr(tmp, 3, ft_strlen(tmp + 3));
		if (!vars->textures[2])
			return (-1);
	}
	else if (fill_textures_vars2(vars, tmp, nb_textures) < 0)
		return (-1);
	return (0);
}

int	fill_map(t_data *vars, int fd, long size, int skip)
{
	char	*tmp;
	int		i;
	int		error;

	i = 0;
	error = 0;
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
