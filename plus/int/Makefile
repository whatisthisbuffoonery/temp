CPP := c++
CPP_FLAG := -Wall -Wextra -Werror -std=c++98
INCLUDES := -I./

NAME := int

SRC := int.cpp main.cpp
OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPP_FLAG) $(OBJ) $(INCLUDES) -o $(NAME)

$(OBJ): %.o: %.cpp
	$(CPP) $(CPP_FLAG) -c $< $(INCLUDES) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
