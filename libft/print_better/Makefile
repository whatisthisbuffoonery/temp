CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c

AR := ar
AR_FLAGS := rcs

NAME := libftprintf.a
FULL := full.a

LIBFT_DIR := ../
LIBFT_LIB := libft

LIBFT_NAME := $(LIBFT_DIR)$(LIBFT_LIB).a

SRC := ft_printf_mand.c arg_mand.c process_mand.c token_mand.c token_call_mand.c \
	   q_func_mand.c tabler_mand.c

OBJ := $(SRC:.c=.o)


all: $(NAME)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_NAME)
	$(AR) $(AR_FLAGS) $@ $(OBJ)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) $< -I$(LIBFT_DIR) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
