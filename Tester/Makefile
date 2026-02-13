CC = cc
CFLAGS = -Wextras -Wall -Werror
MAKE = make
NAME = ft_printft_test
FTPRINTF_DIR = ../
LIBFTPRINTF = $(FTPRINTF_DIR)/libftprintf.a
FILES = ft_printf_test
SRCS = $(addsuffix .c, $(FILES))
HEADERS = $(addsuffix .h, $(FILES))

all: $(NAME)
	./$(NAME)

$(NAME): $(SRCS) $(HEADERS) $(LIBFTPRINTF)
	cc $(SRCS) $(LIBFTPRINTF) -o $(NAME)
	./$(NAME)

$(LIBFTPRINTF): FORCE
	$(MAKE) -C $(FTPRINTF_DIR)

FORCE:



