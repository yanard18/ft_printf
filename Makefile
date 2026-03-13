NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Wextra -Wall -Werror -I./inc -I./libft

SRC_DIR		= src/
SRCS        = $(addprefix $(SRC_DIR), ft_printf.c token.c token_helper.c \
              token_utils.c token_validate.c token_sort.c str_utils.c \
              convert_base.c convert_flags.c convert_padding.c)
OBJS        = $(SRCS:.c=.o)

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

USE_GDB		= 0

ifeq ($(USE_GDB),1)
	CFLAGS += -g
endif

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
libft:
	make -C ./libft
$(LIBFT):
	make -C $(LIBFT_DIR)
	echo $(FILES)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
