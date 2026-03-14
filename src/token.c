/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:09:27 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 20:19:59 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_list	*tokenize(const char **format, t_token *token_table)
{
	t_list	*lst;
	t_token	*out;
	int		prec;

	lst = NULL;
	out = NULL;
	prec = 0;
	while (*++(*format))
	{
		is_token(**format, token_table, &out);
		if (!out || (out->type == PRECISION && prec))
			break ;
		if (out->type == PRECISION)
			prec = 1;
		if (out->type == PRECISION)
			(*format)++;
		push_token(&lst, out);
		if (out->type == SPECIFIER)
			break ;
		if (out->type == PRECISION || out->type == WIDTH)
			int_to_token(format, out);
	}
	if (out && out->type == SPECIFIER)
		(*format)++;
	return (lst);
}

static char	*apply_specifier(t_list *lst, va_list args)
{
	t_token	*token;

	token = (t_token *)ft_lstlast(lst)->content;
	if (token->value[0] == '%')
		return (ft_strdup("%"));
	return (token->f(&(void *){va_arg(args, void *)}, lst));
}

char	*eval_next_token(t_list **lst, t_list *start_lst, char *s)
{
	t_token	*token;

	token = (t_token *)((*lst)->content);
	if (token && token->type != SPECIFIER && token->f)
		s = token->f(s, start_lst);
	*lst = (*lst)->next;
	return (s);
}

char	*read_token(const char **format, va_list args, t_token *table)
{
	t_list		*lst;
	t_list		*start;
	char		*s;
	const char	*rewind;

	rewind = *format;
	lst = tokenize(format, table);
	start = lst;
	if (!validate_tokens(lst))
	{
		ft_lstclear(&lst, free_token);
		*format = rewind + 1;
		if (**format != '\0')
			return (ft_strdup("%"));
		table[16].type = DOWNGRADE;
		return (NULL);
	}
	s = apply_specifier(lst, args);
	sort_tokens(&lst);
	while (lst)
		s = eval_next_token(&lst, start, s);
	ft_lstclear(&start, free_token);
	return (s);
}
