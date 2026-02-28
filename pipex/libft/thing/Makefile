all:
	$(MAKE) -C ../ all
	clang -Wall -Wextra -Werror -g -c parsed.c -I../includes -o parsed.o
	clang -Wall -Wextra -Werror -g parsed.o ../libft.a -I../includes
