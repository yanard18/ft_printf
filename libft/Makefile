CC = cc
AR = ar rcs 
CFLAGS = -Wextra -Werror -Wall
NAME = libft.a
FILES = ft_isalpha \
      ft_isdigit \
      ft_isalnum \
      ft_isascii \
      ft_isprint \
      ft_strlen \
      ft_memset \
      ft_bzero \
      ft_memcpy \
      ft_memmove \
      ft_strlcpy \
      ft_strlcat \
      ft_toupper \
      ft_tolower \
      ft_strchr \
      ft_strrchr \
      ft_strncmp \
      ft_memchr \
      ft_memcmp \
      ft_strnstr \
      ft_atoi \
      ft_calloc \
      ft_strdup \
      ft_substr \
      ft_strjoin \
      ft_strtrim \
      ft_split \
      ft_itoa \
      ft_strmapi \
      ft_striteri \
      ft_putchar_fd \
      ft_putstr_fd \
      ft_putendl_fd \
      ft_putnbr_fd \
      ft_lstnew \
      ft_lstadd_front \
      ft_lstsize \
      ft_lstlast \
      ft_lstadd_back \
      ft_lstdelone \
      ft_lstclear \
      ft_lstiter \
      ft_lstmap

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME) 

run: all
	@$(CC) -L . -l ft -o a.out -fsanitize=address
	@./a.out

$(FILES): %: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean: 
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
