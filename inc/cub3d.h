/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/02/22 19:15:47 by soutin           ###   ########.fr       */
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
	int		x_max;
	int		y_max;
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
typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	void	*texture[3];
	int		size_ximg;
	int		size_yimg;
	int		pos_px;
	int		pos_py;
}			t_data;

void		print_err(char *err_message);

int			exit_and_free(t_data *data);

#endif