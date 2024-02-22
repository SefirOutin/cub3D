/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:09:51 by soutin            #+#    #+#             */
/*   Updated: 2024/02/22 21:46:32 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

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

int	parse(t_vars *vars, char *path)
{
	int		fd;
	char	*tmp;
	int		nb_textures;
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

void	init_img(t_data *data)
{
	int	i;

	i = 0;
	data->texture[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./asset/map_asset/wall.xpm",
			&(data->size_ximg), &(data->size_yimg));
	data->texture[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./asset/map_asset/player.xpm",
			&(data->size_ximg), &(data->size_yimg));
	data->texture[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./asset/map_asset/floor.xpm",
			&(data->size_ximg), &(data->size_yimg));
	while (i < 3)
	{
		if (data->texture[i] == NULL)
		{
			write(2, "Error\nImage no initialise", 26);
			exit_and_free(data);
		}
		i++;
	}
}
void	display_map_2(t_data *data, int *i, int *j)
{
	if (data->map[*j][*i] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture[0],
			(*i * 50), (*j * 50));
	if (data->map[*j][*i] == '0' || data->map[*j][*i] == 'S' ||data->map[*j][*i] == 'E'|| data->map[*j][*i] == 'W' ||data->map[*j][*i] == 'N')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture[2],
			(*i * 50), (*j * 50));
}

void	display_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			display_map_2(data, &i, &j);
			i++;
		}
		i = 0;
		j++;
	}
}
int	main(int argc, char **argv)
{
	t_data	data;
	t_vars	data1;

	parse(&data1, argv[1]);
	data.map = data1.map;
	data.size_ximg = 50;
	data.size_yimg = 50;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, ft_strlen(data.map[0]) * 50,
			ft_arraylen(data.map) * 50, "MazeCub3D");
	if (!data.win_ptr)
		return (free(data.win_ptr), -1);
	init_img(&data);
	display_map(&data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &exit_and_free,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
