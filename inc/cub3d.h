/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/02/28 04:31:22 by bmoudach         ###   ########.fr       */
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

typedef enum e_key
{
	W,
	A,
	S,
	D,
	LEFT,
	RIGHT,
}						t_key;

typedef struct s_pixel_list
{
	int					x;
	int					y;
	int					color;
	struct s_pixel_list	*next;
}						t_pixel_list;

typedef struct s_player
{
	int					forward;
	int					backward;
	int					left;
	int					right;
	int					rotate;
}						t_player;

typedef struct s_data
{
	char				*textures[5];
	int					floor_color[3];
	int					ceilling_color[3];
	int					x_max;
	int					y_max;
	void				*mlx_ptr;
	void				*win_ptr;
	char				**map;
	void				*texture_map[3];
	int					size_ximg;
	int					size_yimg;
	double				pos_px;
	double				pos_py;
	t_player			player_move;
	t_pixel_list		*pixel_list;
}						t_data;

int						get_map_data(t_data *vars, char *path);
int						get_textures(t_data *vars, int fd, int *error);
int						fill_textures_vars(t_data *vars, char *tmp,
							int *nb_textures);
int						fill_textures_vars2(t_data *vars, char *tmp,
							int *nb_textures);
int						fill_colors(int *color_tab, char *tmp);
int						fill_map(t_data *vars, int fd, long size, int skip);
int						skip_map_header(int fd, int *error, int skip);
long					get_map_size(int fd, int *error, int *skip);
long					get_map_size_and_check_is_last(int fd, int *error,
							int *skip);
int						check_map(t_data *vars);
int						parsing(t_data *vars, char *path);
void					init_img(t_data *data);

void					print_err(char *err_message);

int						exit_and_free(t_data *data);
void					erase_square(t_data *data, int x, int y);
void					put_square(int x, int y, t_data *data);
void					display_map(t_data *data);
void					dislay_player(t_data *data);
int						get_inputs(int keysym, t_data *data);
int						release_inputs(int keysym, t_data *data);
int						on_keypress(t_data *data);
void					move(t_data *data, double x, double y);
int						erased_ray(t_data *data);
int						put_ray(t_data *data);
int						convert_map_to_pixel(char **map, int x, int y);

#endif