/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokensort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:13:22 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 20:13:48 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	sort_tokens(t_list **tokens)
{
	t_token	*cur_token;
	t_token	*next_token;
	t_token	*temp_token;
	t_list	*lst_start;
	int		changed;

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

