#include "ft_printf.h"

void debug_lst(void *content)
{
	t_token	*token;
	int	fd;

	fd = 2;
	token = (t_token *)content;
	ft_putchar_fd('\n', fd);
	ft_putchar_fd(token->type, fd);
	ft_putstr_fd("->", 1);
	if (token->value == NULL)
		ft_putstr_fd("NULL", fd);
	else if (token->type == '9')
		ft_putstr_fd(ft_itoa(*((int *)token->value)), fd);
	else
		ft_putstr_fd((char *)token->value, fd);
}
