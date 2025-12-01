CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c
COMPILE_SHARED := -fPIC
SRC := malloc_worse.c
OBJ := malloc_worse.o
NAME := malloc_worse.so
TESTER := dangerous.so
SHARE_LINK := -shared
DLSYM_FLAGS := -ldl #-D_GNU_SOURCE #dlfcn.h uses this

all: $(NAME)

tester: $(TESTER)

$(TESTER): $(OBJ)
	$(CC) $(CC_FLAGS) $(COMPILE_SHARED) -DSEG=1 -o $(OBJ) $(SRC)
	$(CC) $(SHARE_LINK) $(DLSYM_FLAGS) -o $(TESTER) $(OBJ)
	rm -f $(OBJ)

$(NAME): $(OBJ)
	$(CC) $(SHARE_LINK) $(DLSYM_FLAG) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CC_FLAGS) $(COMPILE_SHARED) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(TESTER)

re: fclean all

.PHONY: all clean fclean re
