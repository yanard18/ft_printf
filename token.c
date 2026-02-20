#include "ft_printf.h"

char	*do_nothing(void *content, t_list *tokens)
{
	(void)tokens;
	return (content);
}

t_token flags[4] = {
	(t_token){'f', "#", 10, convert_hash},
	(t_token){'f', "-", 11, do_nothing},
	(t_token){'f', "+", 12, apply_plus_flag},
	(t_token){'0', NULL, 0, NULL}
};

t_token widths[2] = {
	(t_token){'n', NULL, 20, NULL},
	(t_token){'0', NULL, 0, NULL}
};

t_token precision[2] = {
	(t_token){'p', ".", 5, apply_precision},
	(t_token){'0', NULL, 0, NULL}
};

t_token plength[2] = {
	(t_token){'l', NULL, 6, NULL},
	(t_token){'0', NULL, 0, NULL}
};

t_token specifiers[10] = {
	(t_token){'s', "c", 99, itoa},
	(t_token){'s', "s", 99, get_str},
	(t_token){'s', "p", 99, itoa},
	(t_token){'s', "d", 99, itoa},
	(t_token){'s', "i", 99, itoa},
	(t_token){'s', "u", 99, convert_u},
	(t_token){'s', "x", 99, convert_x},
	(t_token){'s', "X", 99, convert_bigx},
	(t_token){'s', "%", 1, NULL},
	(t_token){'0', NULL, 0, NULL}
};

static void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	if (token->type == 'n' || token->type == 'l')
	{
		if (token->value)
			free(token->value);
	}
}

t_token	*get_token_by_type(t_list *lst, const char type)
{
	while (lst->next)
	{
		if (((t_token *)lst->content)->type == type)
			return ((t_token *)lst->content);
		lst = lst->next;
	}
	if (((t_token *)lst->content)->type == type)
		return ((t_token *)lst->content);
	return (NULL);
}

t_token *get_token_by_val(t_list *lst, const char *s)
{
	t_token *token;

	while (lst->next)
	{
		token = (t_token *)lst->content;
		if (ft_strncmp(token->value, s, ft_strlen(s)) == 0)
			return ((t_token *)lst->content);
		lst = lst->next;
	}
	token = (t_token *)lst->content;
	if (ft_strncmp(token->value, s, ft_strlen(s)) == 0)
		return ((t_token *)lst->content);
	return (NULL);

}

int	has_token(const char c, t_token *tokens, t_token **out)
{
	unsigned int	i;

	i = 0;
	while(tokens[i].type != '0')
	{
		if (tokens[i].value[0] == c)
		{
			*out = (tokens + i);
			return (i);
		}
		i++;
	}
	return (-1);
}

static void push_token(t_list **lst, t_token *token)
{

	if (get_token_by_val(*lst, token->value))
	return ;
	ft_lstadd_back(lst, ft_lstnew(token));
}

static t_list	*tokenize(const char **format)
{
	t_list	*lst;
	t_token	*out_token;

	has_token('%', specifiers, &out_token);
	lst = ft_lstnew(out_token);
	(*format)++;
	while (**format && has_token(**format, flags, &out_token) != -1)
	{	
		push_token(&lst, out_token);
		(*format)++;
	}
	if (ft_isdigit(**format))
	{
		widths[0].value = ft_itoa(ft_atoi(*format));
		push_token(&lst, &widths[0]);
	}
	while (ft_isdigit(**format))
	(*format)++;
	if (has_token(**format, precision, &out_token) != -1)
	{
		ft_lstadd_back(&lst, ft_lstnew(&precision[0]));
		(*format)++;
		plength[0].value = ft_itoa(ft_atoi(*format));
		push_token(&lst, &plength[0]);
		while (ft_isdigit(**format))
		(*format)++;
	}
	if (has_token(**format, specifiers, &out_token) != -1)
	{
		push_token(&lst, out_token);
		(*format)++;
	}
	return (lst);
}

char	*apply_specifier(t_list *lst, va_list args)
{
	t_token *token;

	token = (t_token *)ft_lstlast(lst)->content;
	if (ft_strncmp((char *)token->value, "%", 1) == 0)
		return (ft_strdup("%"));
	return (token->f(&(void *){va_arg(args, void *)}, lst));
}

char	*apply_flags(t_list *token_lst, char *s)
{
	t_token *token;
	t_list	*s_lst;

	s_lst = token_lst;
	while (token_lst->next) // read flags
	{
		token = (t_token *)token_lst->content;
		if (token->type == 'f')
			s = token->f(s, s_lst);
		token_lst = token_lst->next;
	}
	return (s);
}

char	*read_precision(t_list *token_lst, char *s)
{
	t_token *token;
	t_list	*s_lst;

	s_lst = token_lst;
	while (token_lst->next) // read flags
	{
		token = (t_token *)token_lst->content;
		if (token->type == 'p')
			s = token->f(s, s_lst);
		token_lst = token_lst->next;
	}
	return (s);
}

char	*apply_width(t_list *token_lst, char *s)
{
	char	*space;
	size_t		val;
	char	*temp_s;
	t_token	*token;

	temp_s = s;
	token = get_token_by_type(token_lst, 'n');
	if (!token)
		return (s);
	val = ft_atoi((char *)token->value);
	if (val <= ft_strlen(s))
		return (s);
	val -= ft_strlen(s);
	space = (char *)malloc(sizeof(char) * val + 1);
	ft_memset(space, 32, val);
	space[val] = 0;
	if (get_token_by_val(token_lst, "-"))
		s = ft_strjoin(s, space);
	else
		s = ft_strjoin(space, s);
	free(space);
	free(temp_s);
	return (s);
}

void	sort_tokens(t_list ** tokens)
{
	t_token	*cur_token;
	t_token	*next_token;
	t_token *temp_token;
	t_list	*lst_start;

	lst_start = *tokens;
	while (1)
	{
		while ((*tokens)->next)
		{
			cur_token = (t_token *)(*tokens)->content;
			next_token = (t_token *)((t_list *)((*tokens)->next)->content);
			if (cur_token->priority > next_token->priority)
			{
				temp_token = cur_token;
				(*tokens)->content = next_token;
				(*tokens)->next->content = temp_token;
			}
			*tokens = (*tokens)->next;
		}
		*tokens = lst_start;
		break ;
	}
}


int validate_tokens(t_list *lst)
{
	if (!lst->next) 
	return (0);
	return (1);
}


ssize_t	read_token(const char **format, va_list args)
{
	t_list	*tokens;
	int valid;
	char	*s;
	size_t	len;		

	tokens = tokenize(format);
	valid = validate_tokens(tokens);
	if (!valid)
	{
		ft_lstclear(&tokens, free_token);
		return (-1);
	}
	//sort_tokens(&tokens);
	//debug_tokenlst(tokens);
	s = apply_specifier(tokens, args);
	s = read_precision(tokens, s);
	s = apply_flags(tokens, s); // take next to skip initial '%'
	s = apply_width(tokens, s);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	free(s);
	ft_lstclear(&tokens, free_token);
	return (len);
}

