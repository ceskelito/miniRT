include libft/mk.var.export/Makefile

# ──────────────────────── #
#      PROJECT CONFIG      #
# ──────────────────────── #
NAME       = minirt
CC         = gcc
RM         = rm -f
MKDIR      = mkdir -p

FT_PATH		= libft
MLX_PATH	= minilibx

CFLAGS     = -Wall -Wextra -Werror -g
IFLAGS  = -I$(MLX_ROOT) -I$(LIBFT_ROOT)/headers -Iincludes
LFLAGS	= -L$(MLX_ROOT)	-lmlx 	\
    	  -L$(LIBFT_ROOT) 	-lft	\
		  -lm 	\
		  -lX11 \
		  -lXext

# ────────────────────── #
#   EXTERNAL LIBRARIES   #
# ────────────────────── #

MLX_ROOT	= minilibx
MLX_NAME 	= libmlx.a

# LIBEZ_ROOT	= ezalloc
# LIBEZ_NAME	= libezalloc.a

MLX			= $(MLX_ROOT)/$(MLX_NAME)
# LIBEZ		= $(LIBEZ_ROOT)/$(LIBEZ_NAME)
LIBFT 		= $(LIBFT_ROOT)/$(LIBFT_NAME)

LIBRARIES 	= $(LIBFT) $(MLX) 

# ──────────────────────── #
#      FILES & FOLDERS     #
# ──────────────────────── #


PARSER 	=	parser			\
			parse_elements	\
			parse_shapes	\
			parse_utils

UTILS 	=	debug		\
			cleanup

FILES	=	main		\
			$(UTILS)	\
			$(PARSER)

OBJ_DIR		= objs
SRC_DIR		= srcs

OBJS		= $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(FILES)))
SRCS 		= $(addsuffix .c, $(FILES))

vpath %.c 	$(SRC_DIR) 			\
			:$(SRC_DIR)/parser	\
			:$(SRC_DIR)/utils

# ──────────────────────── #
#        ANSI COLORS       #
# ──────────────────────── #
RED        := \033[0;31m
GREEN      := \033[0;32m
BLUE       := \033[0;34m
RESET      := \033[0m

# ──────────────────────── #
#       MAIN RULES         #
# ──────────────────────── #
all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(GREEN)Compiling $(BLUE)$<$(RESET)\n"

$(NAME): $(OBJS) $(LIBRARIES)
	@$(CC) $(OBJS) $(LFLAGS) $(LIBRARIES) -o $(NAME)
	@printf "$(GREEN)Linking $(BLUE)$(NAME)$(RESET)\n"	

$(OBJ_DIR):
	$(MKDIR) $@

# ─────────── #
#  LIBRARIES  #
# ─────────── #

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_ROOT)
#
# $(MLX):
# 	$(MAKE) -C $(MLX_ROOT)

$(LIBRARIES):
	$(MAKE) -C $(dir $@)

# ──────────────────────── #
#      CLEANING RULES      #
# ──────────────────────── #

# Project Only
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)
	@echo "\nNote: to propagate the command to the libraries use deep[target] instead\n"

fclean: clean
	$(RM) $(NAME)
	@echo "\nNote: to propagate the command to the libraries use deep[target] instead\n"

re: fclean all

# Project and External Libraries
deepclean: clean
	$(MAKE) clean -C $(LIBFT_ROOT)
	$(MAKE) clean -C $(MLX_ROOT)
	@echo "\n$(GREEN)Deep clean completed.\n$(RESET)"

deepfclean: fclean
	$(MAKE) fclean -C $(LIBFT_ROOT)
#	mlx doesn't have fclean target
	$(MAKE) clean -C $(MLX_ROOT)
	@echo "\n$(GREEN)Deep fclean completed.\n$(RESET)"

deepre: deepfclean all

# ──────────────────────── #
.PHONY: all re clean fclean deepre deepclean deepfclean $(LIBRARIES)
