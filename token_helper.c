/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:59:08 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 22:20:43 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*convert_d(void *content, t_list *tokens)
{
	int		*np;

	(void)tokens;
	np = (int *)content;
	return (ft_itoa(*np));
}


char	*convert_s(void *content, t_list *tokens)
{
	char	**str;

	(void)tokens;
	str = content;
	if (*str == 0)
		return (ft_strdup("(null)"));
	return (ft_strdup(*str));
}
