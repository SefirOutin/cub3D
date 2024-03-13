/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/03/13 22:57:06 by soutin           ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>

# define FOV 90
# define MINI_W 120
# define MINI_H 120
# define WIN_W 1200
# define WIN_H 900
# define PI 3.14159265359

typedef struct s_point
{
	double				x;
	double				y;
}						t_point;

typedef enum e_key
{
	W_KEY,
	A_KEY,
	S_KEY,
	D_KEY,
	LEFT_ROTATE,
	RIGHT_ROTATE,
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
	int					inputs[6][2];
	double				px;
	double				py;
	double				direction;
	int					health;
}						t_player;

typedef struct s_ray
{
	t_point				end;
	t_point				len_one_u;
	t_point				hypo_len_one_u;
	t_point				vlen;
	t_point				v_camera;
	double				len;
	double				angle_rad;
	double				angle_deg;
}						t_ray;

typedef struct s_img
{
	void				*img;
	int					*addr;
	int					bpp;
	int					line_l;
	int					endian;
	int					x;
	int					y;
}						t_img;

typedef struct s_mnmap
{
	void				*textures[6];
	int					x_max;
	int					y_max;
	int					size;
}						t_mnmap;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	char				*textures[5];
	int					floor_color[3];
	int					ceilling_color[3];
	char				**map;
	int					rays_len[360];
	t_img				img;
	t_img				asset[3];
	t_mnmap				mnmap;
	t_player			player;
	t_player            player_mini;
	t_pixel_list		*pixel_list;
}						t_data;

void					init_hook_and_loop(t_data *data);
int						init_mlx_data(t_data *data);
void					init_mnmap_textures(t_data *data);
t_img					init_img(t_data *data, int size_x, int size_y);

int						get_inputs(int keysym, t_data *data);
int						release_inputs(int keysym, t_data *data);
int						on_keypress(t_data *data);
int						mouse(int x, int y, t_data *data);
int						exit_and_free(t_data *data);

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

void					print_err(char *err_message);

int						convert_map_to_pixel(char **map, int x, int y);
void					find_player(t_data *data);
void					display_map(t_data *data);

void					put_square(int x, int y, t_data *data);
void					erase_square(t_data *data, int x, int y);
void					filled_circle_draw(t_data *data, int radius);
void					put_circle_pixels(int radius, t_img *img, int point,
							int xx, int color);
void					filled_circle_erase(t_data *data, int radius);
void					mid_point_circle_draw(t_data *data, int r);
void					mid_point_put_pixels(t_data *data, t_point current,
							int color);
void					mid_point_circle_erase(t_data *data, int r);

void					move(t_data *data, double x, double y,
							double rotation_angle);
int						put_direction(t_data *data, int curr_ray);
void					erase_direction(t_data *data, int len_ray);
double					fix_ang(double a);
int						create_rays(t_data *data);

void					free_section(t_point **section, int size);
int						e_direction(t_data *data, int len_ray, int curr_ray);
void					erase_floors(t_data *data);

void					put_pixel_to_image(t_img *img, int x, int y, int color);
double					deg_to_rad(double degrees);
void					background_img(t_img *img, int size, int color);
void	print_minimap(t_img *win_minimap, t_data *data, t_img *asset);
void	init_asset(t_img *asset, t_data *data);
void	setup_minimap(t_data *data);
void					draw_xpm(t_data *data, double angle);
#endif