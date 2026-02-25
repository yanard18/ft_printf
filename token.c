#include "ft_printf.h"

static t_token g_flags[6] = {
	(t_token){'f', "#", 10, convert_hash},
	(t_token){'f', "-", 11, NULL},
	(t_token){'f', "0", 11, NULL},
	(t_token){'f', " ", 12, convert_space},
	(t_token){'f', "+", 13, convert_plus},
	(t_token){'0', NULL, 0, NULL}
};

static t_token g_widths[2] = {
	(t_token){'n', NULL, 20, convert_width},
	(t_token){'0', NULL, 0, NULL}
};

static t_token g_precision[2] = {
	(t_token){'p', ".", 5, apply_precision},
	(t_token){'0', NULL, 0, NULL}
};

static t_token g_plength[2] = {
	(t_token){'l', NULL, 6, NULL},
	(t_token){'0', NULL, 0, NULL}
};

static t_token g_specifiers[10] = {
	(t_token){'s', "c", 99, convert_d},
	(t_token){'s', "s", 99, convert_s},
	(t_token){'s', "p", 99, convert_p},
	(t_token){'s', "d", 99, convert_d},
	(t_token){'s', "i", 99, convert_d},
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

	if (!*lst)
	{
		*lst = ft_lstnew(token);
		return ;
	}
	if (ft_strncmp(token->value, "%", 1) == 0)
	{
		ft_lstadd_back(lst, ft_lstnew(token));
		return ;
	}
	if (get_token_by_val(*lst, token->value))
		return ;
	else
		ft_lstadd_back(lst, ft_lstnew(token));
}

static t_list	*tokenize(const char **format)
{
	t_list	*lst;
	t_token	*out_token;

	lst = NULL;
	(*format)++;
	while (**format && has_token(**format, g_flags, &out_token) != -1)
	{	
		push_token(&lst, out_token);
		(*format)++;
	}
	if (ft_isdigit(**format))
	{
		g_widths[0].value = ft_itoa(ft_atoi(*format));
		push_token(&lst, &g_widths[0]);
	}
	while (ft_isdigit(**format))
	(*format)++;
	if (has_token(**format, g_precision, &out_token) != -1)
	{
		ft_lstadd_back(&lst, ft_lstnew(&g_precision[0]));
		(*format)++;
		g_plength[0].value = ft_itoa(ft_atoi(*format));
		push_token(&lst, &g_plength[0]);
		while (ft_isdigit(**format))
		(*format)++;
	}
	if (has_token(**format, g_specifiers, &out_token) != -1)
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
	if (token->value[0] == '%')
		return (ft_strdup("%"));
	return (token->f(&(void *){va_arg(args, void *)}, lst));
}

void	sort_tokens(t_list **tokens)
{
	t_token	*cur_token;
	t_token	*next_token;
	t_token *temp_token;
	t_list	*lst_start;
	int changed;

	changed = 0;
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
				changed = 1;
			}
			*tokens = (*tokens)->next;
		}
		*tokens = lst_start;
		if (changed == 0)
		break ;
		changed = 0;
	}
	*tokens = lst_start;
}


int validate_tokens(t_list *lst)
{
	if (!lst) 
	return (0);
	return (1);
}

char *eval_next_token(t_list **lst, t_list *start_lst, char *s)
{
	t_token *token;

	token = (t_token *)((*lst)->content);
	if (token && token->type != 's' && token->f)
	s = token->f(s, start_lst);
	*lst = (*lst)->next;
	return (s);
}

ssize_t	read_token(const char **format, va_list args)
{
	t_list	*lst;
	t_list	*start_lst;
	int 	valid;
	char	*s;
	size_t	len;		

	lst = tokenize(format);
	//debug_tokenlst(lst);
	start_lst = lst;
	valid = validate_tokens(lst);
	if (!valid)
	{
		ft_lstclear(&lst, free_token);
		return (-1);
	}
	s = apply_specifier(lst, args);
	sort_tokens(&lst);
	while (lst)
		s = eval_next_token(&lst, start_lst, s);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	free(s);
	ft_lstclear(&start_lst, free_token);
	return (len);
}
