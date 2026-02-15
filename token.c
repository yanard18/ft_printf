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

static void	push_token(t_list **lst, char type, void *value)
{
	t_list	*newlst;

	newlst = ft_lstnew(new_token(type, value));
	ft_lstadd_back(lst, newlst);
}

static void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

static char	*strdup_firstchr(const char *s)
{
	char	*ret;

	ret = (char *)malloc(2);
	if (!ret)
		return (NULL);
	*ret = *s;
	*(ret + 1) = '\0';
	return (ret);
}

static t_list	*tokenize(const char **format)
{
	t_list	*lst;

	lst = ft_lstnew(new_token('%', NULL));
	while (**format)
	{
		(*format)++;
		if (**format == '#' || **format == '-' || **format == '+')
		{
			push_token(&lst, 'f', strdup_firstchr(*format));
		}
		else if (ft_isdigit(**format))
		{
			int n = ft_atoi(*format);
			char *s = ft_itoa(n);
			push_token(&lst, '9', s);
			while (ft_isdigit(**format))
				(*format)++;
			(*format)--;
		}
		else if (**format == 'd')
		{
			push_token(&lst, 'c', ft_strdup("d"));
		}
	}
	return (lst);
}

static void	debug_token(void *content)
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

static void	debug_tokenlst(t_list *tokens)
{
	ft_lstiter(tokens, debug_token);
	ft_putchar_fd('\n', 1);
}

void	read_token(const char **format)
{
	t_list	*tokens;

	tokens = tokenize(format);
	debug_tokenlst(tokens);
	ft_lstclear(&tokens, free_token);
}


