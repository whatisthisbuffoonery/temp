NAME := libft.a
FULL := full.a
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c
AR := ar
AR_FLAGS := rcs
HEADER := libft.h
MAND_AR := mand.a

SRC := ft_atoi.c ft_bzero.c ft_calloc.c \
ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

BONUS_SRC := ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJ := $(SRC:.c=.o)

BONUS_OBJ := $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(FULL)

$(NAME): $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

$(MAND_AR): $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

$(FULL): $(MAND_AR) $(BONUS_OBJ)
	cp -p $(MAND_AR) $(FULL)
	$(AR) $(AR_FLAGS) $(FULL) $(BONUS_OBJ)
	cp $(FULL) $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

$(BONUS_OBJ): %.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(MAND_AR) $(FULL)

re: fclean all

.PHONY: all clean fclean re bonus
