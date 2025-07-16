NAME = cub3d
CC = cc 
FLAGS = -Wall -Wextra -Werror -pedantic -g

# Include paths
INCLUDES = -I./include -I./MLX42/include -I./libft_divinus

# Libraries
MLX42_DIR = ./MLX42
LIBFT_DIR = ./libft_divinus
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Source files
SRC = ./src/main.c \
	  ./src/parser/parser.c ./src/parser/extract_texture.c ./src/parser/extract_colors.c \
	  ./src/parser/ft_isspace.c

OBJ = $(SRC:.c=.o)

# Link flags for MLX42 (varies by OS)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LINKS = -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LINKS = -lglfw -L"/opt/homebrew/lib/" -framework Cocoa -framework OpenGL -framework IOKit
endif

all: $(NAME)

# Build MLX42 using cmake
$(MLX42_LIB):
	@echo "Building MLX42..."
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build

# Build libft
$(LIBFT_LIB):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(MLX42_LIB) $(LIBFT_LIB) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX42_LIB) $(LIBFT_LIB) $(LINKS) -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re
