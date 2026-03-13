/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:09:27 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/13 23:02:32 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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
	t_token	*out_token;

	lst = NULL;
	while (*++(*format))
	{
		is_token(**format, token_table, &out_token);
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
	}
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

char	*read_token(const char **format, va_list args, t_token *token_table)
{
	t_list		*lst;
	t_list		*start_lst;
	int			valid;
	char		*s;
	const char	*rewind_str_addr;

	rewind_str_addr = *format;
	lst = tokenize(format, token_table);
	start_lst = lst;
	valid = validate_tokens(lst);
	if (!valid)
	{
		ft_lstclear(&lst, free_token);
		*format = rewind_str_addr + 1;
		token_table[16].type = DOWNGRADE;
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
