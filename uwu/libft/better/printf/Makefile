LIBFT_DIR := ../..
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES := -I$(LIBFT_DIR)/includes -Iincludes
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g
AR := ar
AR_FLAGS := rcs
__SRC := char_op.c str_op.c int_op.c uint_op.c hex_op.c ft_printf.c symbol.c fill.c #gaga.c
NAME := libftprintf.a

SRC_DIR := src
OBJ_DIR := obj
OLD_DIR := old

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(__SRC))

all: $(NAME)

gaga:
	cc gaga.c libftprintf.a -I includes/ 2>/dev/null
	./a.out

$(NAME): $(OBJ) $(LIBFT)
	cp $(LIBFT) $(NAME)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJ)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
