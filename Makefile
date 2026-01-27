# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#              #
#    Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minirt

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./libft/headers -I./minilibx
LIBS		= -L./libft -lft -L./minilibx -lmlx -lXext -lX11 -lm

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parser/parse_utils.c \
			  $(SRC_DIR)/parser/parse_utils2.c \
			  $(SRC_DIR)/parser/parse_types.c \
			  $(SRC_DIR)/parser/parse_values.c \
			  $(SRC_DIR)/parser/parse_ambient.c \
			  $(SRC_DIR)/parser/parse_camera.c \
			  $(SRC_DIR)/parser/parse_light.c \
			  $(SRC_DIR)/parser/parse_sphere.c \
			  $(SRC_DIR)/parser/parse_plane.c \
			  $(SRC_DIR)/parser/parse_cylinder.c \
			  $(SRC_DIR)/parser/parse_scene.c \
			  $(SRC_DIR)/scene/scene_utils.c \
			  $(SRC_DIR)/scene/scene_cleanup.c \
			  $(SRC_DIR)/error/error_handling.c \
			  $(SRC_DIR)/debug/debug_print.c \
			  $(SRC_DIR)/debug/debug_objects.c \
			  $(SRC_DIR)/debug/debug_scene.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT		= ./libft/libft.a
MLX			= ./minilibx/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C ./libft

clean:
	@rm -rf $(OBJ_DIR)
	@make -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
