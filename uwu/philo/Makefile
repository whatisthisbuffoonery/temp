

LIBFT_DIR := ../libft

INCLUDES := -I$(LIBFT_DIR)/includes

LIBS := -L$(LIBFT_DIR) -lpthread -lft

NAME := philo

SRC := main.c init.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME) :$(OBJ) h_philo.h
	$(CC) $(CCFLAGS) $(OBJ) $(LIBS) $(INCLUDES) -o $(NAME)
