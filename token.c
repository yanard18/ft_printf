#include "ft_printf.h"

t_token flags[4] = {
	(t_token){'f', "#", itoa},
	(t_token){'f', "-", itoa},
	(t_token){'f', "+", apply_plus_flag},
	(t_token){'0', NULL, NULL}
};

t_token specifiers[10] = {
	(t_token){'s', "c", itoa},
	(t_token){'s', "s", get_str},
	(t_token){'s', "p", itoa},
	(t_token){'s', "d", itoa},
	(t_token){'s', "i", itoa},
	(t_token){'s', "u", itoa},
	(t_token){'s', "x", hex_small},
	(t_token){'s', "X", itoa},
	(t_token){'s', "%", NULL},
	(t_token){'0', NULL, NULL}
};

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
	if (token->type == 'n')
	{
		if (token->value)
			free(token->value);
	}
}

int	has_token(const char c, t_token *tokens, t_token **out)
{
	unsigned int	i;

	i = 0;
	while(tokens[i].type != '0')
	{
		if (((char *)tokens[i].value)[0] == c)
		{
			*out = (tokens + i);
			return (i);
		}
		i++;
	}
	return (0);
}

static t_list	*tokenize(const char **format)
{
	t_list	*lst;
	t_token	*out_token;

	has_token('%', specifiers, &out_token);
	lst = ft_lstnew(out_token);
	while (**format)
	{
		(*format)++;
		if (has_token(**format, flags, &out_token))
		{
			ft_lstadd_back(&lst, ft_lstnew(out_token));
		}
		else if (ft_isdigit(**format))
		{
			push_token(&lst, 'n', ft_itoa(ft_atoi(*format)));
			while (ft_isdigit(**format))
				(*format)++;
			(*format)--;
		}
		else if (**format == '.')
		{
		}
		else if (has_token(**format, specifiers, &out_token))
		{
			ft_lstadd_back(&lst, ft_lstnew(out_token));
			(*format)++;
			break ;
		}
	}
	return (lst);
}

char	*apply_specifier(t_list *lst, va_list args)
{
	t_token *token;

	while (lst->next)
		lst = lst->next;
	token = (t_token *)lst->content;
	if (ft_strncmp((char *)token->value, "d", 1) == 0)
		return (token->f(&(int){va_arg(args, int)}));
	if (ft_strncmp((char *)token->value, "x", 1) == 0)
		return (token->f(&(int){va_arg(args, int)}));
	else if (ft_strncmp((char *)token->value, "s", 1) == 0)
		return (token->f((char *){va_arg(args, char *)}));

	return (ft_strdup(""));
}

char	*apply_flags(t_list *token_lst, char *s)
{
	t_token *token;

	while (token_lst->next) // read flags
	{
		token = (t_token *)token_lst->content;
		if (token->type == 'f')
			s = token->f(s);
		token_lst = token_lst->next;
	}
	return (s);
}

void	read_token(const char **format, va_list args)
{
	t_list	*token_lst;
	char	*s;

	token_lst = tokenize(format);
	//debug_tokenlst(token_lst);
	s = apply_specifier(token_lst, args);
	s = apply_flags(token_lst, s); // take next to skip initial '%'
	ft_putstr_fd(s, 1);
	free(s);
	ft_lstclear(&token_lst, free_token);
}
