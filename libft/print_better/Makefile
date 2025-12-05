CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c

AR := ar
AR_FLAGS := rcs

NAME := libftprintf.a
FULL := full.a

LIBFT_DIR := ..
LIBFT_LIB := libft

SRC := ft_printf.c arg.c process.c token.c token_call.c \
	   q_func.c

SRC_MAND := tabler_mand.c type_bus_mand.c handle_flag_mand.c \
			arg_help_mand.c

OBJ := $(SRC:.c=.o)

OBJ_MAND := $(SRC_MAND:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAND)
	$(MAKE) -C $(LIBFT_DIR) bonus
	cp -r $(LIBFT_DIR)/$(LIBFT_LIB).a ./$(NAME)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJ) $(OBJ_MAND)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) $< -I$(LIBFT_DIR) -o $@

$(OBJ_MAND): %.o: %.c
	$(CC) $(CC_FLAGS) $< -I$(LIBFT_DIR) -o $@

clean:
	rm -f $(OBJ) $(OBJ_MAND)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
