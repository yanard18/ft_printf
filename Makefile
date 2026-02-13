CC			= cc
CFLAGS		= -Wextra -Wall -Werror
NAME		= libftprintf.a
FILES		= ft_printf
MAKE		= make
LIBFT		= libft/libft.a
LIBFT_DIR	= libft/
SRCS		= $(addsuffix .c, $(FILES))
OBJS		= $(addsuffix .o, $(FILES))

all: $(NAME) 

.ONESHELL:
$(NAME): $(LIBFT) $(OBJS)
	ar -M << EOF
	CREATE $(NAME)
	ADDLIB $(LIBFT)
	ADDMOD $(OBJS)
	SAVE
	END
	EOF

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
