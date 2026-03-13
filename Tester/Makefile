CC           = cc
CFLAGS       = -Wextra -Wall -Werror
INCLUDES     = -I. -I$(FTPRINTF_DIR)inc 

MAKE         = make
NAME         = ft_printf_test
FTPRINTF_DIR = ../
LIBFTPRINTF  = $(FTPRINTF_DIR)libftprintf.a
FILES        = ft_printf_test test_bonus test_guryel
SRCS         = $(addsuffix .c, $(FILES))
HEADERS      = ft_printf_test.h

all: $(NAME)
	valgrind --leak-check=full ./$(NAME)

$(NAME): $(SRCS) $(HEADERS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LIBFTPRINTF) -Wno-format -o $(NAME)

$(LIBFTPRINTF): FORCE
	$(MAKE) bonus -C $(FTPRINTF_DIR) USE_GDB=1

clean:
	rm -f $(NAME)

fclean: clean

FORCE:

.PHONY: all clean fclean FORCE

