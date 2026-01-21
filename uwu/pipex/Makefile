CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g
NAME := pipex
LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_NAME := ft

SRC := main.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) -I $(LIBFT_DIR)/includes -o $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -I $(LIBFT_DIR)/includes -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all
