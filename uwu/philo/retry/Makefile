CC := clang
CC_FLAGS := -Wall -Wextra -Werror -g -pthread
NAME := philo
BONUS := philo_bonus
MAND_DIR := mand
INCLUDES := includes

SRC := main.c init.c handles.c print.c philo.c utils.c timeval.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CC_FLAGS) $(OBJ) -latomic -I $(INCLUDES) -o $(NAME)

$(OBJ): %.o: $(MAND_DIR)/%.c $(INCLUDES)/h_philo.h
	$(CC) $(CC_FLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
