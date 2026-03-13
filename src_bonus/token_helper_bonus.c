/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:59:08 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/13 23:02:05 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

char	*convert_c(void *content, t_list *tokens)
{
	char	*ret;
	char	c;

	(void)tokens;
	c = *((char *)content);
	ret = malloc(2);
	if (!ret)
		return (NULL);
	if (c == '\0')
		ret[0] = '\1';
	else
		ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
