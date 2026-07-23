CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g -pthread
NAME := philo
BONUS := philo_bonus
LIBFT_DIR := ../../libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_NAME := ft

SRC := main.c init_philo.c init_maint.c mutex.c print.c run.c table.c utils.c timeval.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MAND_OBJ)
	$(CC) $(CC_FLAGS) $(OBJ) $(MAND_OBJ) -latomic -o $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	rm -rf $(OBJ) $(MAND_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -rf $(NAME) $(FULL)

re: fclean all

.PHONY: all clean fclean re bonus
