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

char	*convert_plus(void *content, t_list *tokens)
{
	char	*s;
	char	*ret;

	(void)tokens;
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

	if (((char *)content)[0] == '-')
		return ((char *)content);
	if (get_token_by_val(tokens, "d"))
	{
		s = ft_strjoin(" ", (char *)content);
		free(content);
		return (s);
	}
	return ((char *)content);
}

char	*convert_hash(void *content, t_list *tokens)
{
	t_token	*token;

	token = get_token_by_type(tokens->next, 's');
	if (token && token->value[0] == 'x')
		return (add_hex_prefix(content, 0));
	if (token && token->value[0] == 'X')
		return (add_hex_prefix(content, 1));
	return ((char *)content);
}
