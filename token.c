#include "ft_printf.h"

static void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	if (token->type == WIDTH || token->type == PRECISION)
		{
			if (token->value)
				{
					free(token->value);
					token->value = NULL;
				}
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

static int	is_token(const char c, t_token *tokens, t_token **out)
{
	unsigned int	i;

	i = 0;
	*out = NULL;
	while(tokens[i].type != '0')
	{
		if ((tokens[i].value != NULL && tokens[i].value[0] == c)
			|| (tokens[i].type == PRECISION && c == '.')
			|| (tokens[i].type == WIDTH && ft_isdigit(c)))
			{
				*out = (tokens + i);
				return (1);
			}
		i++;
	}
	return (0);
}

static void push_token(t_list **lst, t_token *token)
{

	if (!*lst)
	{
		*lst = ft_lstnew(token);
		return ;
	}
	if (token->value && token->value[0] == '%')
	{
		ft_lstadd_back(lst, ft_lstnew(token));
		return ;
	}
	if (token->value && get_token_by_val(*lst, token->value))
		return ;
	else
		ft_lstadd_back(lst, ft_lstnew(token));
}

static void int_to_token(const char **format, t_token *out_token)
{
	if (!out_token)
		return ;
	out_token->value = ft_itoa(ft_atoi(*format));
	while (ft_isdigit(**format))
		(*format)++;
	(*format)--;
}

static t_list	*tokenize(const char **format, t_token *g_token_buf)
{
	t_list	*lst;
	t_token	*out_token;

	lst = NULL;
	while (*++(*format))
		{
			is_token(**format, g_token_buf, &out_token);
			if (out_token)
				{
					push_token(&lst, out_token);
					if (out_token->type == PRECISION)
						(*format)++;
					if (out_token->type == PRECISION || out_token->type == WIDTH)
							int_to_token(format, out_token);
					else if (out_token->type == SPECIFIER)
						{
							(*format)++;
							break ;
						}
				}
			else
				return (lst);
			//out_token = NULL;
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

static void	sort_tokens(t_list **tokens)
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
	if(get_token_by_type(lst, SPECIFIER) == NULL)
		return (0);
	return (1);
}

char *eval_next_token(t_list **lst, t_list *start_lst, char *s)
{
	t_token *token = (t_token *)((*lst)->content);

	if (token && token->type != SPECIFIER && token->f)
		s = token->f(s, start_lst);
	*lst = (*lst)->next;
	return (s);
}

char *read_token(const char **format, va_list args, t_token *g_token_buf)
{
	t_list	*lst;
	t_list	*start_lst;
	int 	valid;
	char	*s;
	const char	*rewind_str_addr;

	rewind_str_addr = *format;
	lst = tokenize(format, g_token_buf);
	start_lst = lst;
	valid = validate_tokens(lst);
	if (!valid)
	{
		ft_lstclear(&lst, free_token);
		*format = rewind_str_addr + 1;
		g_token_buf[16].type = DOWNGRADE;
		if (**format == '\0')
			return (NULL);
		return (ft_strdup("%"));
	}
	s = apply_specifier(lst, args);
	sort_tokens(&lst);
	while (lst)
		s = eval_next_token(&lst, start_lst, s);
	ft_lstclear(&start_lst, free_token);
	return (s);
}
