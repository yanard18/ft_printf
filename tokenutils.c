/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:48:08 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 19:01:29 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

t_token	*get_token_by_val(t_list *lst, const char *s)
{
	t_token	*token;

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

int	is_token(const char c, t_token *tokens, t_token **out)
{
	unsigned int	i;

	i = 0;
	*out = NULL;
	while (tokens[i].type != '0')
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

void	push_token(t_list **lst, t_token *token)
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

void	int_to_token(const char **format, t_token *out_token)
{
	if (!out_token)
		return ;
	out_token->value = ft_itoa(ft_atoi(*format));
	while (ft_isdigit(**format))
		(*format)++;
	(*format)--;
}
