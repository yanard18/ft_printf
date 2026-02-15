#include "ft_printf.h"

char	*itoa(void *content)
{
	int		*np;

	np = (int *)content;

	return (ft_itoa(*np));
}

char	*apply_plus_flag(void *content)
{
	char	*s;
	char	*ret;
	int		len;


	s = (char *)content;
	ret = ft_strjoin("+", s);
	free(s);
	return (ret);

}
t_token flags[3] = {
	(t_token){'f', "#", itoa},
	(t_token){'f', "-", itoa},
	(t_token){'f', "+", apply_plus_flag}
};

t_token specifiers[2] = {
	(t_token){'%', NULL, NULL},
	(t_token){'d', NULL, itoa}
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

	lst = ft_lstnew(&specifiers[0]);
	while (**format)
	{
		(*format)++;
		if (**format == '#')
			ft_lstadd_back(&lst, ft_lstnew(&flags[0]));
		else if (**format == '-')
			ft_lstadd_back(&lst, ft_lstnew(&flags[1]));
		else if (**format == '+')
			ft_lstadd_back(&lst, ft_lstnew(&flags[2]));
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
		else if (**format == 'd')
		{
			ft_lstadd_back(&lst, ft_lstnew(&specifiers[1]));
			(*format)++;
			break ;
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

void	read_token(const char **format, va_list args)
{
	t_list	*tokens;
	t_list	*llist;
	t_list	*start_lst;
	t_token *ltoken;
	t_token *token;
	char	*s;


	tokens = tokenize(format);
	start_lst = tokens;
	llist = tokens;
	while (llist->next)
		llist = llist->next;
	ltoken = (t_token *)llist->content;

	if (ltoken->type == 'd') // read specifier token
	{
		int x = 4;
		s = ltoken->f(&x);
	}
	tokens = tokens->next; // skip % token
	while (tokens->next) // read flags
	{
		token = (t_token *)tokens->content;
		s = token->f(s);
		tokens = tokens->next;
	}

	ft_putstr_fd(s, 1);
	free(s);

	debug_tokenlst(tokens);
	ft_lstclear(&start_lst, free_token);
}


