/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/02/26 18:17:56 by bmoudach         ###   ########.fr       */
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
typedef struct s_data
{
	char	*textures[5];
	int		floor_color[3];
	int		ceilling_color[3];
	int		x_max;
	int		y_max;
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	void	*texture_map[3];
	int		size_ximg;
	int		size_yimg;
	int		pos_px;
	int		pos_py;
}			t_data;

int			get_map_data(t_data *vars, char *path);
int			get_textures(t_data *vars, int fd, int *error);
int			fill_textures_vars(t_data *vars, char *tmp, int *nb_textures);
int			fill_textures_vars2(t_data *vars, char *tmp, int *nb_textures);
int			fill_colors(int *color_tab, char *tmp);
int			fill_map(t_data *vars, int fd, long size, int skip);
int			skip_map_header(int fd, int *error, int skip);
long		get_map_size(int fd, int *error, int *skip);
long		get_map_size_and_check_is_last(int fd, int *error, int *skip);
int			check_map(t_data *vars);

void		print_err(char *err_message);

int			exit_and_free(t_data *data);

#endif