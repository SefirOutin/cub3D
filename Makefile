# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soutin <soutin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 04:10:09 by soutin            #+#    #+#              #
#    Updated: 2024/04/02 20:14:39 by soutin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		:=		srcs
OBJ_DIR		:=		objs
SRC_BONUS_DIR		:=		srcs_bonus
OBJ_BONUS_DIR		:=		objs_bonus
LIBFT_DIR	=		libft

NAME		=		cub3D
NAME_BONUS	=		cub3D_b

SRC			=		srcs/main.c \
					srcs/parsing/get_player_data.c \
					srcs/parsing/get_map_data.c \
					srcs/parsing/get_map_data_utils.c \
					srcs/parsing/parsing.c \
					srcs/parsing/check_type.c \
					srcs/parsing/check_img.c \
					srcs/exit_free.c \
					srcs/graphic/init_textures.c \
					srcs/move_event/hook.c\
					srcs/move_event/event.c \
					srcs/graphic/ray.c \
					srcs/graphic/math_utils.c \
					srcs/graphic/setup_minimap.c \
					srcs/graphic/view.c \
					srcs/init.c \
					srcs/mlx_engine/destroy_image.c \
					srcs/mlx_engine/get_pixel_img.c \
					srcs/mlx_engine/draw_vertical_line.c \
					srcs/mlx_engine/init_img.c \
					srcs/mlx_engine/put_img_to_img.c \
					srcs/mlx_engine/put_img_to_mini_img.c \
					srcs/mlx_engine/put_pixel_img.c \
					srcs/mlx_engine/put_pixel_mini_img.c \
					srcs/mlx_engine/filled_circle_draw.c \

SRC_BONUS	=		srcs_bonus/main_bonus.c \
					srcs_bonus/parsing/get_player_data_bonus.c \
					srcs_bonus/parsing/get_map_data_bonus.c \
					srcs_bonus/parsing/get_map_data_utils_bonus.c \
					srcs_bonus/parsing/parsing_bonus.c \
					srcs_bonus/parsing/check_type_bonus.c \
					srcs_bonus/parsing/check_img_bonus.c \
					srcs_bonus/exit_free_bonus.c \
					srcs_bonus/graphic/init_textures_bonus.c \
					srcs_bonus/move_event/hook_bonus.c\
					srcs_bonus/move_event/event_bonus.c \
					srcs_bonus/graphic/ray_bonus.c \
					srcs_bonus/graphic/math_utils_bonus.c \
					srcs_bonus/graphic/setup_minimap_bonus.c \
					srcs_bonus/graphic/view_bonus.c \
					srcs_bonus/init_bonus.c \
					srcs_bonus/mlx_engine/destroy_image_bonus.c \
					srcs_bonus/mlx_engine/get_pixel_img_bonus.c \
					srcs_bonus/mlx_engine/draw_vertical_line_bonus.c \
					srcs_bonus/mlx_engine/init_img_bonus.c \
					srcs_bonus/mlx_engine/put_img_to_img_bonus.c \
					srcs_bonus/mlx_engine/put_img_to_mini_img_bonus.c \
					srcs_bonus/mlx_engine/put_pixel_img_bonus.c \
					srcs_bonus/mlx_engine/put_pixel_mini_img_bonus.c \
					srcs_bonus/mlx_engine/filled_circle_draw_bonus.c \

OBJ			=		$(SRC:$(SRC)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS	=		$(SRC_BONUS:$(SRC_BONUS)/%.c=$(OBJ_BONUS_DIR)/%.o)


LIBFT		=		libft/libft.a

CC			=		clang
CPPFLAGS	=		-I./inc -I./libft/inc
MLX			=		-L./minilibx-linux
MLXFLAGS	=		-lm -lmlx -lX11 -lXext
CFLAGS		=		-Wall -Werror -Werror -g3

$(NAME):			$(OBJ) 
						$(MAKE) -C minilibx-linux
						$(MAKE) -C $(LIBFT_DIR)
						$(CC) $(CFLAGS) $(CPPFLAGS) $(MLX) $(OBJ) $(MLXFLAGS) -o $(NAME) $(LIBFT)

$(NAME_BONUS):			$(OBJ_BONUS) 
						$(MAKE) -C minilibx-linux
						$(MAKE) -C $(LIBFT_DIR)
						$(CC) $(CFLAGS) $(CPPFLAGS) $(MLX) $(OBJ_BONUS) $(MLXFLAGS) -o $(NAME_BONUS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:				$(NAME)

bonus:				$(NAME_BONUS)

clean:
					$(MAKE) clean -C $(LIBFT_DIR)

fclean:				clean
						rm -f $(NAME)
						rm -f $(NAME_BONUS)
						$(MAKE) fclean -C $(LIBFT_DIR)

re:					fclean all

.PHONY:				all clean fclean re