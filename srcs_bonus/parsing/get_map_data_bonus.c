/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:28 by bmoudach          #+#    #+#             */
/*   Updated: 2024/04/08 15:40:54 by soutin           ###   ########.fr       */
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
		return (close(fd), -1);
	size = get_map_size_and_check_is_last(fd, &error, &skip);
	if (size < 0)
		return (free_static_tab(data->main.textures_path), close(fd), -1);
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
			return (free(tmp), free_static_tab(data->main.textures_path),
				-1);
		free(tmp);
		skip++;
	}
	if (check_path_img(data->main.textures_path))
		return (-1);
	if (nb_textures != 6)
		return (print_err("missing information"), -1);
	data->main.textures_path[4] = NULL;
	return (skip);
}

int	fill_map(t_data *data, int fd, long size, int skip)
{
	char	*tmp;
	int		i;
	int		error;

	i = 0;
	error = 0;
	if (skip_map_header(fd, &error, skip) < 0)
		return (close(fd), -1);
	while (i < size)
	{
		tmp = get_next_line(fd, &error);
		if (error)
			return (close(fd), -1);
		if (!ft_strncmp(tmp, "\n", 2))
		{
			free(tmp);
			break ;
		}
		data->map[i] = dup_line(tmp);
		free(tmp);
		if (!data->map[i])
			return (close(fd), -1);
		i++;
	}
	return (data->map[i] = NULL, close(fd), 0);
}
