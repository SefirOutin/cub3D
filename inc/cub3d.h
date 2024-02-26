/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/02/26 16:27:21 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_vars
{
	char	*textures[5];
	int		floor_color[3];
	int		ceilling_color[3];
	char	**map;
}			t_vars;

int			get_map_data(t_vars *vars, char *path);
int			get_textures(t_vars *vars, int fd, int *error);
int			fill_textures_vars(t_vars *vars, char *tmp, int *nb_textures);
int			fill_textures_vars2(t_vars *vars, char *tmp, int *nb_textures);
int			fill_colors(int *color_tab, char *tmp);
int			fill_map(t_vars *vars, int fd, long size, int skip);
int			skip_map_header(int fd, int *error, int skip);
long		get_map_size(int fd, int *error, int *skip);
long		get_map_size_and_check_is_last(int fd, int *error, int *skip);
int			check_map(t_vars *vars);

void		print_err(char *err_message);

#endif