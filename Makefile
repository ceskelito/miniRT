include libft/mk.var.export/Makefile

# ──────────────────────── #
#        ANSI COLORS       #
# ──────────────────────── #
RED        := \033[0;31m
GREEN      := \033[0;32m
BLUE       := \033[0;34m
RESET      := \033[0m

# ──────────────────────── #
#      PROJECT CONFIG      #
# ──────────────────────── #
NAME       = minirt
CC         = gcc
RM         = rm -f
MKDIR      = mkdir -p

CFLAGS     = -Wall -Wextra -Werror

IFLAGS  = -I$(MLX_ROOT) 	\
		  -I$(LIBFT_INCS) 	\
		  -Iincludes

LFLAGS	= -L$(MLX_ROOT)		\
    	  -L$(LIBFT_ROOT) 	\
		  -lmlx \
		  -lft	\
		  -lm 	\
		  -lX11 \
		  -lXext

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=minilibx.supp

# ────────────────────── #
#   EXTERNAL LIBRARIES   #
# ────────────────────── #

MLX_ROOT	= minilibx
MLX_NAME 	= libmlx.a

MLX			= $(MLX_ROOT)/$(MLX_NAME)
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

MLX_S 	=	init			\
			render			\
			events_hooks	\
			print_legend	\
			mlx_imglib

# Vector math and ray-object intersection
VECTOR	=	vector		\
			hit

# Per-shape intersection routines
OBJECTS	=	objects			\
			objects_utils	\
			objects_cone	\
			objects_torus

COLOR	=	color

FILES	=	main		\
			$(UTILS)	\
			$(PARSER)	\
			$(MLX_S)	\
			$(VECTOR)	\
			$(OBJECTS)	\
			$(COLOR)

OBJ_DIR		= objs
SRC_DIR		= srcs

OBJS		= $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(FILES)))
SRCS 		= $(addsuffix .c, $(FILES))

vpath %.c 	$(SRC_DIR)			\
			:$(SRC_DIR)/parser	\
			:$(SRC_DIR)/utils	\
			:$(SRC_DIR)/mlx		\
			:$(SRC_DIR)/vector	\
			:$(SRC_DIR)/objects	\
			:$(SRC_DIR)/color

# ──────────────────────── #
#       MAIN RULES         #
# ──────────────────────── #

all: $(NAME)

debug: CFLAGS += -g3

debug: all

run: DEFAULT_RT = scenes/example.rt

run: debug
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(if $(RT_FILE),$(RT_FILE),$(DEFAULT_RT))

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(GREEN)Compiling $(BLUE)$<$(RESET)\n"

$(NAME): $(OBJS) | $(LIBRARIES)
	@$(CC) $(OBJS) $(LFLAGS) $(LIBRARIES) -o $(NAME)
	@printf "$(GREEN)Linking $(BLUE)$(NAME)$(RESET)\n"	

$(OBJ_DIR):
	$(MKDIR) $@

# ─────────── #
#  LIBRARIES  #
# ─────────── #

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
	$(MAKE) clean -C $(MLX_ROOT) #	mlx doesn't have fclean target
	@echo "\n$(GREEN)Deep fclean completed.\n$(RESET)"

deepre: deepfclean all

# ──────────────────────── #
.PHONY: debug run all re clean fclean deepre deepclean deepfclean
