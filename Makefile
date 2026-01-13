include libft/mk.var.export/Makefile

# ──────────────────────── #
#      PROJECT CONFIG      #
# ──────────────────────── #
NAME       = minirt
# CC         = gcc
RM         = rm -f
MKDIR      = mkdir -p

CFLAGS     = -Wall -Wextra -Werror
IFLAGS  = -I$(MLX_PATH) -I$(FT_PATH)/headers -Iincludes
LFLAGS	= -L$(MLX_PATH)	-lmlx 	\
    	  -L$(FT_PATH) 	-lft	\
		  -lm 	\
		  -lX11 \
		  -lXext


FT_PATH		= libft
MLX_PATH	= minilibx-linux

MLX_LIB		= $(MLX_PATH)/libmlx.a
LIBRARIES	= $(FT_PATH)/libft.a

# ──────────────────────── #
#      FILES & FOLDERS     #
# ──────────────────────── #

FILES		= main.c 	

O_DIR		= objs
S_DIR		= sources

OBJS		= $(addprefix $(O_DIR)/, $(FILES:%.c=%.o))
SRCS 		= $(addprefix $(S_DIR)/, $(FILES))

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

$(O_DIR)/%.o: $(S_DIR)/%.c | $(O_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(GREEN)Compiling $(BLUE)$<$(RESET)\n"

$(NAME): $(OBJS) $(LIBRARIES) | $(BIN_DIR)
	@if [ ! -f "$(MLX_LIB)" ]; then \
		echo "$(RED)\nNOTE: The minilibx-linux library is not compiled, and is necessary in order to link $(NAME).\n$(RESET)"; \
		echo "$(BLUE)Please compile it manually by running $(GREEN)'make -C minilibx-linux'$(BLUE),"; \
		echo "or running $(GREEN)'make'$(BLUE) in the $(GREEN)minilibx$(BLUE) directory.$(RESET)\n"; \
		exit 1; \
	else \
		printf "$(GREEN)\n- Minilibx-linux library is compiled yet. -\n\n$(RESET)"; \
	fi
	@$(CC) $(OBJS) $(LFLAGS) $(LIB_NAMES) -no-pie -o $(NAME)
	@printf "$(GREEN)Linking $(BLUE)$(NAME)$(RESET)\n"	

$(BIN_DIR) $(O_DIR):
	$(MKDIR) $@

# ──────────────────────── #
#    LIBRARY COMPILATION   #
# ──────────────────────── #

# MLX Data Library
$(MLXD_NAME): $(MLXD_OBJS)

$(MLXD_OBJS): $(MLXD_SRCS)
	$(MAKE) -C $(MLXD_PATH)

# Libft Library
$(FT_PATH)/libft.a: $(LIBFT_OBJS)

$(LIBFT_OBJS): $(LIBFT_SRCS)
	$(MAKE) -C $(FT_PATH)

# ──────────────────────── #
#      CLEANING RULES      #
# ──────────────────────── #
# Project Only
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Project and External Libraries
deepclean: clean
	$(MAKE) clean -C $(MLXD_PATH)
	$(MAKE) clean -C $(COLORS_PATH)
	$(MAKE) clean -C $(FT_PATH)
	@echo "\n$(GREEN)Deep clean completed.\n$(RESET)"
	@echo "$(RED)Note: This will not remove the minilibx-linux library files.$(RESET)"
	@echo "$(BLUE)You can do that by running $(GREEN)'make clean -C minilibx-linux'$(BLUE) from here, "
	@echo "or by running $(GREEN)'make clean'$(BLUE) in the minilibx-linux directory.\n$(RESET)"

deepfclean: fclean
	$(MAKE) fclean -C $(MLXD_PATH)
	$(MAKE) fclean -C $(FT_PATH)
	@echo "\n$(GREEN)Deep fclean completed.\n$(RESET)"
	@echo "$(RED)Note: This will not remove the minilibx-linux library files.$(RESET)"
	@echo "$(BLUE)You can do that by running $(GREEN)'make clean -C minilibx-linux'$(BLUE) from here, "
	@echo "or by running $(GREEN)'make clean'$(BLUE) in the minilibx-linux directory.\n$(RESET)"

deepre: deepfclean all

# ──────────────────────── #
.PHONY: all re clean fclean deepre deepclean deepfclean
