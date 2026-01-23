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

CFLAGS     = -Wall -Wextra -Werror
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

FILES		= main \
			scene \
			parse_scene \
			parse_line \
			parse_utils \
			parse_elements_a \
			parse_elements_light \
			parse_elements_b \
			parse_elements_plane \
			parse_elements_c \
			debug_print \
			debug_print_entities_a \
			debug_print_entities_b \
			debug_print_utils

O_DIR		= objs
S_DIR		= srcs

OBJS		= $(addsuffix .o, $(addprefix $(O_DIR)/, $(FILES)))
SRCS 		= $(addsuffix .c, $(FILES))

vpath %.c $(S_DIR)

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

$(O_DIR)/%.o: %.c | $(O_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(GREEN)Compiling $(BLUE)$<$(RESET)\n"

$(NAME): $(OBJS) $(LIBRARIES)
	# @if [ ! -f "$(MLX_LIB)" ]; then \
	# 	echo "$(RED)\nNOTE: The minilibx-linux library is not compiled, and is necessary in order to link $(NAME).\n$(RESET)"; \
	# 	echo "$(BLUE)Please compile it manually by running $(GREEN)'make -C minilibx-linux'$(BLUE),"; \
	# 	echo "or running $(GREEN)'make'$(BLUE) in the $(GREEN)minilibx$(BLUE) directory.$(RESET)\n"; \
	# 	exit 1; \
	# else \
	# 	printf "$(GREEN)\n- Minilibx-linux library is compiled yet. -\n\n$(RESET)"; \
	# fi
	@$(CC) $(OBJS) $(LFLAGS) $(LIB_NAMES) -o $(NAME)
	@printf "$(GREEN)Linking $(BLUE)$(NAME)$(RESET)\n"	

$(O_DIR):
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
	$(MAKE) clean -C $(MLX_ROOT) #mlx doesn't have fclean target
	@echo "\n$(GREEN)Deep fclean completed.\n$(RESET)"

deepre: deepfclean all

# ──────────────────────── #
.PHONY: all re clean fclean deepre deepclean deepfclean $(LIBRARIES)
