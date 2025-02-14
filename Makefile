# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR)						\
	 -Wall -Wextra -Wsign-conversion -pedantic -Werror	\
	 -O3

# Headers.
INC_DIR = include

# Source files.
SRC_DIR = src
SRC_FILES = main.c							\
	    	utils.c							\
		parse/ft_parse.c parse/ft_is_map_closed.c		\
		parse/ft_player_count.c					\
		parse/ft_process_tabs_in_map.c parse/ft_save_colors.c	\
		parse/ft_save_textures.c parse/ft_map_clean_validate.c	\
		parse/ft_map_clean_validate_utils.c parse/utils.c	\
		init/init.c init/free_content.c init/utils.c		\
		controls.c						\
		render/ft_render.c render/ray_cast.c			\
		render/draw_line_pixel_and_set_texture.c render/utils.c

SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files.
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Name of the resulting binary file.
NAME = cub3D

# For other Makefiles.
EXTERNAL_DIR = external
MAKE = make

# Libft.
LIBFT_DIR = $(EXTERNAL_DIR)/Libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)
LIBFT_CLEAN = fclean

# minilibx-linux.
MLX_DIR = $(EXTERNAL_DIR)/minilibx-linux
LIBMLX_A = $(MLX_DIR)/libmlx.a
LIBMLX_LINUX_A = $(MLX_DIR)/libmlx_Linux.a
MLX = $(MLX_DIR)/$(MLX_BUILD_TARGET)
MLX_CLEAN = clean

# Targets.
all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX_A) $(LIBMLX_LINUX_A) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -L$(LIBFT_DIR) -lft	\
		-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)			# Create the $(OBJ_DIR) if it doesn't exist.
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_NAME)

$(LIBMLX_A):
	$(MAKE) -C $(MLX_DIR) $(MLX_BUILD_TARGET)

$(LIBMLX_LINUX_A):
	$(MAKE) -C $(MLX_DIR) $(MLX_BUILD_TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_CLEAN)
	$(MAKE) -C $(MLX_DIR) $(MLX_CLEAN)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
