# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soutin <soutin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 04:10:09 by soutin            #+#    #+#              #
#    Updated: 2024/03/29 17:18:24 by soutin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		:=		srcs
OBJ_DIR		:=		objs
LIBFT_DIR	=		libft

NAME		=		cub3D
SRC			=		srcs/main.c \
					srcs/parsing/get_player_data.c \
					srcs/parsing/get_map_data.c \
					srcs/parsing/get_map_data_utils.c \
					srcs/parsing/parsing.c \
					srcs/exit_free.c \
					srcs/graphic/init_textures.c \
					srcs/move_event/hook.c\
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

OBJ			=		$(SRC:$(SRC)/%.c=$(OBJ_DIR)/%.o)

LIBFT		=		libft/libft.a

CC			=		clang
CPPFLAGS	=		-I./inc -I./libft/inc
MLX			=		-L./minilibx-linux
MLXFLAGS	=		-lm -lmlx -lX11 -lXext 
CFLAGS		=		-Wall -Werror -Werror -gdwarf-4
$(NAME):			$(OBJ) 
						$(MAKE) -C minilibx-linux
						$(MAKE) -C $(LIBFT_DIR)
						$(CC) $(CFLAGS) $(CPPFLAGS) $(MLX) $(OBJ) $(MLXFLAGS) -o $(NAME) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:				$(NAME)

clean:
					rm -rf $(OBJ_DIR)
					$(MAKE) clean -C $(LIBFT_DIR)

fclean:				clean
						rm -f $(NAME)
						$(MAKE) fclean -C $(LIBFT_DIR)

re:					fclean all

.PHONY:				all clean fclean re