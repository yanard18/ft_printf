/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:51:40 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/12 01:52:55 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	sort_tokens(t_list **tokens)
{
	int		changed;
	t_list	*curr;
	t_token	*t1;
	t_token	*t2;

	changed = 1;
	while (changed && tokens && *tokens)
	{
		changed = 0;
		curr = *tokens;
		while (curr->next)
		{
			t1 = curr->content;
			t2 = curr->next->content;
			if (t1->priority > t2->priority)
			{
				curr->content = t2;
				curr->next->content = t1;
				changed = 1;
			}
			curr = curr->next;
		}
	}
}
