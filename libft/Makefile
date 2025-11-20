NAME := libft.a
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c
AR := ar
AR_FLAGS := rcs
HEADER := libft.h

dot_o := ft_atoi.o ft_bzero.o ft_calloc.o \
ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o \
ft_itoa.o ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o ft_lstdelone.o \
ft_lstiter.o ft_lstlast.o ft_lstmap.o ft_lstnew.o ft_lstsize.o \
ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o \
ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o ft_split.o \
ft_strchr.o ft_strdup.o ft_striteri.o ft_strjoin.o ft_strlcat.o \
ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o \
ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o

all: $(NAME)

$(NAME): $(dot_o)
	$(AR) $(AR_FLAGS) $@ $^

ft_atoi.o: ft_atoi.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_bzero.o: ft_bzero.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_calloc.o: ft_calloc.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_isalnum.o: ft_isalnum.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_isalpha.o: ft_isalpha.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_isascii.o: ft_isascii.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_isdigit.o: ft_isdigit.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_isprint.o: ft_isprint.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_itoa.o: ft_itoa.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstadd_back.o: ft_lstadd_back.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstadd_front.o: ft_lstadd_front.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstclear.o: ft_lstclear.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstdelone.o: ft_lstdelone.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstiter.o: ft_lstiter.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstlast.o: ft_lstlast.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstmap.o: ft_lstmap.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstnew.o: ft_lstnew.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_lstsize.o: ft_lstsize.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_memchr.o: ft_memchr.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_memcmp.o: ft_memcmp.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_memcpy.o: ft_memcpy.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_memmove.o: ft_memmove.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_memset.o: ft_memset.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_putchar_fd.o: ft_putchar_fd.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_putendl_fd.o: ft_putendl_fd.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_putnbr_fd.o: ft_putnbr_fd.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_putstr_fd.o: ft_putstr_fd.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_split.o: ft_split.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strchr.o: ft_strchr.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strdup.o: ft_strdup.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_striteri.o: ft_striteri.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strjoin.o: ft_strjoin.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strlcat.o: ft_strlcat.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strlcpy.o: ft_strlcpy.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strlen.o: ft_strlen.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strmapi.o: ft_strmapi.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strncmp.o: ft_strncmp.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strnstr.o: ft_strnstr.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strrchr.o: ft_strrchr.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_strtrim.o: ft_strtrim.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_substr.o: ft_substr.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_tolower.o: ft_tolower.c
	$(CC) $(CC_FLAGS) $< -o $@
ft_toupper.o: ft_toupper.c
	$(CC) $(CC_FLAGS) $< -o $@

clean:
	rm -f $(dot_o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
