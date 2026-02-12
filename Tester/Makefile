CC = cc
ARGS = -Wall -Werror -Wextra
NAME = ft_printf_test
PRINTF_LIB = ftprintf.a

all: $(NAME)
	@./$(NAME)

$(NAME): ft_printf_test.c printf_tester.h $(PRINTF_LIB)
		 @$(CC) ft_printf_test.c $(ARGS) $(PRINTF_LIB) ../libft/libft.a -o $(NAME)

$(PRINTF_LIB): ft_printf.o
	ar rcs ftprintf.a ft_printf.o

ft_printf.o: ../ft_printf.c
	$(CC) ../libft/libft.a ../ft_printf.c -o ft_printf.o -c

clean:
	rm $(NAME)
	rm ftprintf.a

fclean: clean

.PHONY: all clean fclean


