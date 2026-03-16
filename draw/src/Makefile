MLX_DIR := ../minilibx-linux
LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES := -I$(MLX_DIR) -I$(LIBFT_DIR)/includes
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g
SRC := main.c loop.c view.c frame.c ras.c xiaoxiao.c
LIBS := -lm -lXext -lX11 -lmlx -lft -L$(MLX_DIR) -L$(LIBFT_DIR) -L/usr/lib/X11
OBJ := $(SRC:.c=.o)
MLX := $(MLX_DIR)/libmlx.a
NAME := fdf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX) h_mlx.h
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBS) $(INCLUDES) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX):
	$(MAKE) -C $(MLX_DIR) all

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
