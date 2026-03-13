NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wextra -Wall -Werror -I./inc -I./libft

DIR         = src/
SRCS        = $(addprefix $(DIR), ft_printf.c token.c token_helper.c \
              token_utils.c token_validate.c token_sort.c str_utils.c \
              convert_base.c convert_flags.c convert_padding.c)
OBJS        = $(SRCS:.c=.o)

BONUS_DIR   = src_bonus/
BONUS_SRCS  = $(addprefix $(BONUS_DIR), ft_printf_bonus.c token_bonus.c token_helper_bonus.c \
              token_utils_bonus.c token_validate_bonus.c token_sort_bonus.c str_utils_bonus.c \
              convert_base_bonus.c convert_flags_bonus.c convert_padding_bonus.c)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

LIBFT_DIR   = libft/
LIBFT       = $(LIBFT_DIR)libft.a

USE_GDB     = 0

ifeq ($(USE_GDB),1)
    CFLAGS += -g
endif

all: $(NAME) 

$(LIBFT):
	@make -C $(LIBFT_DIR)

.ONESHELL:
$(NAME): $(LIBFT) $(OBJS)
	ar -M << EOF
	CREATE $(NAME)
	ADDLIB $(LIBFT)
	ADDMOD $(OBJS)
	SAVE
	END
	EOF

bonus: .bonus

.ONESHELL:
.bonus: $(LIBFT) $(BONUS_OBJS)
	ar -M << EOF
	CREATE $(NAME)
	ADDLIB $(LIBFT)
	ADDMOD $(BONUS_OBJS)
	SAVE
	END
	EOF
	@touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f .bonus

re: fclean all

.PHONY: all clean fclean re bonus
