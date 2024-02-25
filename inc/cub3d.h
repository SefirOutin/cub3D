/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/02/25 16:04:48 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_vars
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*floor_color;
	char	*ceilling_color;
	char	**map;
}			t_vars;


int			get_map_data(t_vars *vars, char *path);
int			get_textures(t_vars *vars, int fd, int *error);
int			fill_textures_vars(t_vars *vars, char *tmp, int *nb_textures);
int			fill_textures_vars2(t_vars *vars, char *tmp, int *nb_textures);
int			fill_map(t_vars *vars, char *path, size_t size, int skip);
int			skip_map_header(int fd, int *error, int skip);
size_t		get_map_size(int fd, int *error, int *skip);

#endif