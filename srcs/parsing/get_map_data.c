/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:52:16 by soutin            #+#    #+#             */
/*   Updated: 2024/03/29 17:17:42 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_data(t_data *data, char *path)
{
	int		fd;
	int		error;
	int		skip;
	long	size;

	error = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n"), perror("map file"), -1);
	skip = get_textures(data, fd, &error);
	if (skip < 0)
		return (-1);
	size = get_map_size_and_check_is_last(fd, &error, &skip);
	if (size < 0)
		return (-1);
	data->map = ft_calloc(size + 1, sizeof(char *));
	if (!data->map)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n"), perror("map file"), -1);
	if (fill_map(data, fd, size, skip) < 0)
		return (-1);
	return (0);
}

int	get_textures(t_data *data, int fd, int *error)
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
		if (fill_textures_data(data, tmp, &nb_textures) < 0)
			return (free(tmp), -1);
		free(tmp);
		skip++;
	}
	if (nb_textures != 6)
		return (print_err("missing information"), -1);
	data->main.textures_path[4] = NULL;
	return (skip);
}

int	fill_textures_data2(t_data *data, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("WE ", tmp, 3) && ++(*nb_textures))
	{
		data->main.textures_path[3] = ft_substr(tmp, 3, ft_strlen(tmp + 3) - 1);
		if (!data->main.textures_path[3])
			return (-1);
	}
	else if (!ft_strncmp("F ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(&data->main.floor_color, tmp + 1))
			return (print_err("invalid color"), -1);
	}
	else if (!ft_strncmp("C ", tmp, 2) && ++(*nb_textures))
	{
		if (fill_colors(&data->main.ceilling_color, tmp + 1))
			return (print_err("invalid color"), -1);
	}
	else if (!ft_strncmp(tmp, "\n", 2))
		return (0);
	else
		return (print_err("header"), -1);
	return (0);
}

int	fill_textures_data(t_data *data, char *tmp, int *nb_textures)
{
	if (!ft_strncmp("NO ", tmp, 3) && ++(*nb_textures))
	{
		data->main.textures_path[0] = ft_substr(tmp, 3, ft_strlen(tmp + 3) - 1);
		if (!data->main.textures_path[0])
			return (-1);
	}
	else if (!ft_strncmp("EA ", tmp, 3) && ++(*nb_textures))
	{
		data->main.textures_path[1] = ft_substr(tmp, 3, ft_strlen(tmp + 3) - 1);
		if (!data->main.textures_path[1])
			return (-1);
	}
	else if (!ft_strncmp("SO ", tmp, 3) && ++(*nb_textures))
	{
		data->main.textures_path[2] = ft_substr(tmp, 3, ft_strlen(tmp + 3) - 1);
		if (!data->main.textures_path[2])
			return (-1);
	}
	else if (fill_textures_data2(data, tmp, nb_textures) < 0)
		return (-1);
	return (0);
}

int	fill_map(t_data *data, int fd, long size, int skip)
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
		data->map[i] = dup_line(tmp);
		if (!data->map[i])
			return (-1);
		i++;
		free(tmp);
	}
	return (data->map[i] = NULL, close(fd), 0);
}
