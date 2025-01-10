# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR) -Wall -Wextra -Wsign-conversion -pedantic -Werror -O3

# Archiver options.
ARC = ar
ARCFLAGS = rcs

# Headers.
INC_DIR = include

# Source files.
SRC_DIR = src
SRC_FILES = ft_isspace.c ft_isupper.c ft_islower.c ft_isalpha.c	\
			ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c	\
			ft_strlen.c ft_strnlen.c ft_memset.c ft_bzero.c		\
			ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c	\
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c	\
			ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c	\
			ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c		\
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_strtok_r.c	\
			ft_split_free.c ft_split.c ft_itoa.c ft_strmapi.c	\
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c		\
			ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c			\
			ft_lstadd_front.c ft_lstsize.c ft_lstlast.c			\
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c		\
			ft_lstiter.c ft_lstmap.c ft_lstswap.c ft_lstat.c	\
			ft_lstremove_at.c ft_lstremove_node.c				\
			ft_lstinsert_at.c ft_strcspn.c get_next_line.c		\
			ft_printf/ft_printf.c ft_printf/ft_vfprintf_fd.c	\
			ft_printf/ft_vfprintf_fd_handle_format.c			\
			ft_printf/specifiers/ft_printf_putchar_fd.c			\
			ft_printf/specifiers/ft_printf_putstr_fd.c			\
			ft_printf/specifiers/ft_printf_putnbr_base_fd.c		\
			ft_printf/specifiers/ft_printf_putptr_fd.c			\
			ft_printf/specifiers/ft_printf_putnbr_fd.c
SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files.
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Name of the resulting binary file.
NAME = libft.a

# Targets.
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(ARC) $(ARCFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)			# Create $(OBJ_DIR) if it doesn't exist.
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
