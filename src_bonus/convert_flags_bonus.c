/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:58:55 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/12 01:58:58 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_hex_prefix(void *content, int capitalize)
{
	char	*s;
	char	*ret;

	s = (char *)content;
	if (*s == '0' && *(s + 1) == '\0')
		return (s);
	if (capitalize == 0)
		ret = ft_strjoin("0x", s);
	else
		ret = ft_strjoin("0X", s);
	free(s);
	return (ret);
}

char	*convert_plus(void *content, t_list *tokens)
{
	char	*s;
	char	*ret;

	s = (char *)content;
	if (*s == '-')
		return (s);
	if (!get_token_by_val(tokens, "d") && !get_token_by_val(tokens, "i"))
		return (s);
	ret = ft_strjoin("+", s);
	free(s);
	return (ret);
}

char	*convert_space(void *content, t_list *tokens)
{
	char	*s;

	s = (char *)content;
	if (*s == '-')
		return (s);
	if (get_token_by_val(tokens, "+"))
		return (s);
	if (get_token_by_val(tokens, "d") || get_token_by_val(tokens, "i"))
	{
		s = ft_strjoin(" ", (char *)content);
		free(content);
		return (s);
	}
	return (s);
}

char	*convert_hash(void *content, t_list *tokens)
{
	t_token	*token;

	token = get_token_by_type(tokens, 's');
	if (token && token->value[0] == 'x')
		return (add_hex_prefix(content, 0));
	if (token && token->value[0] == 'X')
		return (add_hex_prefix(content, 1));
	return ((char *)content);
}
