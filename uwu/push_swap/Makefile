CC := clang
CC_FLAGS := -Wall -Wextra -Werror
LIBFT_DIR := ../libft
LIBFT := libft

SRC := init.c main.c merge_sort.c op.c radix.c #turk.c
OBJ := $(SRC:.c=.o)

NAME := push_swap

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT).a
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT).a -o $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(LIBFT_DIR)/$(LIBFT).a:
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
