NAME := libft.a
FULL := full.a
CC := clang
CC_FLAGS := -Wall -Wextra -Werror -c -g
AR := ar
AR_FLAGS := rcs
HEADER := libft.h
MAND_AR := mand.a
INCLUDE_DIR := includes
OBJ_DIR := obj
GNL_DIR := gnl
FT_DIR := ft
PRINTF_DIR := printf

FT_SRC := ft_atoi.c ft_atoi_ind.c ft_atohu_ind.c ft_bzero.c ft_calloc.c ht_init.c \
min.c max2.c ft_abs.c \
ft_swap.c ft_swapf.c \
ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isquote.c ft_ishex.c ft_isspace.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_putnbr.c ft_putstr.c ft_putchar.c \
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strcmp.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
parsed_argsplit.c malloc_cond.c

BONUS_SRC := ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

GNL_SRC := get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line.c get_next_line_utils.c

PRINTF_SRC := ft_printf.c arg.c process.c token.c token_call.c q_func.c arg_help.c \
tabler_bonus.c type_bus_bonus.c handle_flag_bonus.c

FT_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(FT_SRC))

BONUS_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))

GNL_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(GNL_SRC))

PRINTF_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(PRINTF_SRC))

OBJ := $(FT_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_DIR) $(FULL)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

$(MAND_AR): $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

$(FULL): $(MAND_AR) $(BONUS_OBJ)
	cp -p $(MAND_AR) $(FULL)
	$(AR) $(AR_FLAGS) $(FULL) $(BONUS_OBJ)
	cp $(FULL) $(NAME)

$(FT_OBJ): $(OBJ_DIR)/%.o: $(FT_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

$(BONUS_OBJ): $(OBJ_DIR)/%.o: $(FT_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

$(GNL_OBJ): $(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

$(PRINTF_OBJ): $(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	$(CC) $(CC_FLAGS) -I $(INCLUDE_DIR) $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(MAND_AR) $(FULL)

re: fclean all

.PHONY: all clean fclean re bonus
