/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:10:44 by soutin            #+#    #+#             */
/*   Updated: 2024/04/02 20:12:01 by soutin           ###   ########.fr       */
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

# define FOV 66
# define MINI_W 240
# define MINI_H 240
# define WIN_W 1200
# define WIN_H 900
# define PI 3.14159265359
# define SHIFT_AMOUNT 16 // 2^16 = 65536
# define SHIFT_MASK ((1 << SHIFT_AMOUNT) - 1)

typedef struct s_dpoint
{
	double		x;
	double		y;
}				t_dpoint;

typedef struct s_ipoint
{
	int			x;
	int			y;
}				t_ipoint;

typedef enum e_key
{
	W_KEY,
	A_KEY,
	S_KEY,
	D_KEY,
	LEFT_ROTATE,
	RIGHT_ROTATE,
}				t_key;

typedef struct s_player
{
	int			inputs[6][2];
	t_dpoint	pos;
	double		direction;
}				t_player;

typedef struct s_ray
{
	t_dpoint	end;
	t_dpoint	len_one_u;
	t_dpoint	hypo_len_one_u;
	t_dpoint	vlen;
	t_dpoint	v_camera;
	t_ipoint	step;
	int			side;
	double		len;
	double		angle_rad;
	double		angle_deg;
}				t_ray;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_l;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_mnmap
{
	t_img		asset[3];
	void		*textures[6];
	int			size;
	int			w;
	int			h;
	int			x;
	int			y;
}				t_mnmap;

typedef struct s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			w;
	int			h;

}				t_win;

typedef struct s_main_img
{
	t_img		view;
	char		*textures_path[5];
	int			floor_color;
	int			ceilling_color;
	int			nb_rays;
	t_img		textures[5];
	t_ray		*rays;

}				t_main_img;

typedef struct s_data
{
	t_win		win;
	char		**map;
	t_main_img	main;
	t_mnmap		minimap;
	t_player	player;
	t_player	player_mini;
}				t_data;

// MLX engine
int				init_img(t_data *data, t_img *img, int width, int height);
void			put_pixel_to_image(t_img *img, int x, int y, int color);
void			filled_circle_draw(t_img *img, int x, int y, int radius);
void			destroy_image(void *ptr, t_data *data);
void			put_pixel_img(t_img *img, int x, int y, int color);
void			draw_vertical_line(t_img *img, t_ipoint start, int len,
					int color);
void			put_img_to_img(t_img *dst, t_img src, int x, int y);
unsigned int	get_pixel_img(t_img img, int x, int y);
void			put_img_to_mini_img(t_img *dst, t_img src, t_ipoint point,
					int size);
void			put_pixel_mini_img(t_img *img, int x, int y, int color);
void			draw_xpm(t_data *data, double angle);

void			init_hook_and_loop(t_data *data);
int				init_mlx_data(t_data *data);
void			init_minimap_textures(t_data *data);
void			init_asset(t_img *asset, t_data *data);
void			init_textures(t_data *data);
void			first_display(t_data *data);

// Hook functions
int				get_inputs(int keysym, t_data *data);
int				release_inputs(int keysym, t_data *data);
int				on_keypress(t_data *data);
int				mouse(int x, int y, t_data *data);
int				exit_and_free(t_data *data);

// Parsing
int				parsing(t_data *data, char *path);
int				get_map_data(t_data *data, char *path);
int				get_textures(t_data *data, int fd, int *error);
int				fill_textures_data(t_data *data, char *tmp, int *nb_textures);
int				fill_textures_data2(t_data *data, char *tmp, int *nb_textures);
int				fill_colors(int *color_tab, char *tmp);
int				fill_map(t_data *data, int fd, long size, int skip);
int				skip_map_header(int fd, int *error, int skip);
long			get_map_size(int fd, int *error, int *skip);
long			get_map_size_and_check_is_last(int fd, int *error, int *skip);
int				check_map(t_data *data);
void			find_player(t_data *data);
char			*dup_line(char *tmp);

int				create_rays(t_data *data);
int				view(t_data *data);
void			create_minimap(t_data *data);

void			move(t_data *data, double x, double y, double rotation_angle);
void			print_err(char *err_message);

double			fix_ang(double a);
double			deg_to_rad(double degrees);

void			free_imgs_error(t_data *data, t_img *imgs, int size);
int	check_type(char *path, char *type);
int	check_path_img(char **array);

#endif