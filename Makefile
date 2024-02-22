# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 04:10:09 by soutin            #+#    #+#              #
#    Updated: 2024/02/22 19:38:28 by bmoudach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		:=		srcs
OBJ_DIR		:=		objs
LIBFT_DIR	=		libft

NAME		=		cub3D
SRC			=		srcs/main.c
OBJ			=		$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT		=		libft/libft.a

CC			=		clang
CPPFLAGS	=		-I./inc -I./libft/inc
MLX			=		-L./minilibx-linux
MLXFLAGS	=		-lmlx -lX11 -lXext
CFLAGS		=		-Wall -Werror -Werror -g3

$(NAME):			$(OBJ) 
						$(MAKE) -C minilibx-linux
						$(MAKE) -C $(LIBFT_DIR)
						$(CC) $(CFLAGS) $(CPPFLAGS) $(MLX) -lm $(OBJ) $(MLXFLAGS) -o $(NAME) $(LIBFT)

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:				$(NAME)

clean:
					rm -rf $(OBJ_DIR)
					# $(MAKE) clean -C $(LIBFT_DIR)

fclean:				clean
						rm -f $(NAME)
						$(MAKE) fclean -C $(LIBFT_DIR)

re:					fclean all

.PHONY:				all clean fclean re