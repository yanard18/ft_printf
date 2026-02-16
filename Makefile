CC			= cc
CFLAGS		= -Wextra -Wall -Werror
NAME		= libftprintf.a
FILES		= ft_printf token token_debug
MAKE		= make
LIBFT		= libft/libft.a
LIBFT_DIR	= libft/
SRCS		= $(addsuffix .c, $(FILES))
OBJS		= $(addsuffix .o, $(FILES))
USE_GDB		= 0

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
	echo $(FILES)
	
$(OBJS): %.o: %.c
ifeq ($(USE_GDB),1)
	$(CC) $(CFLAGS) -g $^ -c -o $@
else
	$(CC) $(CFLAGS) $^ -c -o $@
endif

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
