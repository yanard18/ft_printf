#include "ft_printf.h"

void	debug_token(void *content)
{
	t_token	*token;
	int	fd;

	fd = 1;
	token = (t_token *)content;
	ft_putchar_fd('\n', fd);
	ft_putchar_fd(token->type, fd);
	ft_putstr_fd("->", 1);
	if (token->value == NULL)
		ft_putstr_fd("NULL", fd);
	else
		ft_putstr_fd((char *)token->value, fd);
}

void	debug_tokenlst(t_list *tokens)
{
	ft_lstiter(tokens, debug_token);
	ft_putchar_fd('\n', 1);
}
