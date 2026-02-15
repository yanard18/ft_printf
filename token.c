#include "ft_printf.h"

static	t_token *new_token(char type, void *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
	{
		ft_putstr_fd("free_token: token is null", 2);
		return ;
	}
	if (token->value)
		free(token->value);
	free(token);
}

t_list	*tokenize(const char **format)
{
	t_list	*lst;
	t_token	*token;

	lst = ft_lstnew(new_token('%', NULL));
	return (lst);
}

void	read_token(const char **format)
{
	t_list	*tokens;

	tokens = tokenize(format);
	(*format)++;
	ft_lstclear(&tokens, free_token);
}
