#include "ft_printf.h"

char	*itoa(void *content)
{
	int		*np;

	np = (int *)content;
	return (ft_itoa(*np));
}

char	*hex_small(void *content)
{
	long	n;      // Using long to safely handle INT_MIN
	long	temp;
	int		len;
	int		is_neg;
	char	*str;
	char	*base = "0123456789abcdef";

	n = *(int *)content; 
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	temp = n;
	len = (n == 0) ? 1 : 0;
	while (temp != 0)
	{
		temp /= 16;
		len++;
	}
	len += is_neg;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[--len] = base[n % 16];
		n /= 16;
	}
	if (is_neg)
		str[0] = '-';
	return (str);

}

char	*apply_plus_flag(void *content)
{
	char	*s;
	char	*ret;
	int		len;

	s = (char *)content;
	if (*s == '-')
		return (s);
	ret = ft_strjoin("+", s);
	free(s);
	return (ret);

}

t_token flags[4] = {
	(t_token){'f', "#", itoa},
	(t_token){'f', "-", itoa},
	(t_token){'f', "+", apply_plus_flag},
	(t_token){'0', NULL, NULL}
};

t_token specifiers[10] = {
	(t_token){'s', "c", itoa},
	(t_token){'s', "s", itoa},
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

int	has_pattern(const char c, t_token *tokens, t_token **out)
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

	lst = ft_lstnew(&specifiers[0]);
	while (**format)
	{
		(*format)++;
		if (has_pattern(**format, flags, &out_token))
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
		else if (has_pattern(**format, specifiers, &out_token))
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
	int x = va_arg(args, int);
	token = (t_token *)lst->content;
	return (token->f(&x));
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
	debug_tokenlst(token_lst);
	s = apply_specifier(token_lst, args);
	s = apply_flags(token_lst, s); // take next to skip initial '%'
	ft_putstr_fd(s, 1);
	free(s);
	ft_lstclear(&token_lst, free_token);
}
