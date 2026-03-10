CC = cc
CFLAGS = -Wextra -Wall -Werror
MAKE = make
NAME = ft_printft_test
FTPRINTF_DIR = ../
LIBFTPRINTF = $(FTPRINTF_DIR)/libftprintf.a
FILES = ft_printf_test test_basic test_other
SRCS = $(addsuffix .c, $(FILES))
HEADERS = ft_printf_test.h

all: $(NAME)
	valgrind --leak-check=full ./$(NAME)

$(NAME): $(SRCS) $(HEADERS) $(LIBFTPRINTF)
	cc $(SRCS) $(LIBFTPRINTF) -Wformat -o $(NAME)

$(LIBFTPRINTF): FORCE
	$(MAKE) -C $(FTPRINTF_DIR) USE_GDB=1

clean:
	rm $(NAME)

fclean: clean

FORCE:

.PHONY: all FORCE


