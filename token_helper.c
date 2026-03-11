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

char	*convert_width(void *str, t_list *lst)
{
	char	*space;
	size_t	val;
	char	c;

	c = ' ';
	if (get_token_by_val(lst, "-") && get_token_by_val(lst, "-")->type == FLAG)
		c = ' ';
	else if (get_token_by_val(lst, "0") && get_token_by_val(lst, "0")->type == FLAG)
		c = '0';
	val = ft_atoi(get_token_by_type(lst, 'w')->value);
	if (val <= ft_strlen((char *)str))
		return ((char *)str);
	val -= ft_strlen((char *)str);
	space = (char *)malloc(sizeof(char) * val + 1);
	ft_memset(space, c, val);
	space[val] = 0;
	if (get_token_by_val(lst, "-"))
		str = (char *)strjoin_safe((char *)str, space);
	else
		str = (char *)strjoin_safe(space, (char *)str);
	return ((char *)str);
}

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

char	*apply_precision(void *content, t_list *tokens)
{
	t_token	*spec;
	char	*ret;
	char	*zero_str;
	size_t	prec;

	spec = get_token_by_type(tokens->next, 's');
	prec = ft_atoi(get_token_by_type(tokens, '.')->value);
	if (prec <= ft_strlen((char *)content))
		return ((char *)content);
	prec -= ft_strlen((char *)content);
	if (spec && (spec->value[0] == 'd' || spec->value[0] == 'x'))
	{
		zero_str = (char *)malloc(prec + 1);
		ft_memset(zero_str, '0', prec);
		zero_str[prec] = '\0';
		ret = ft_strjoin(zero_str, (char *)content);
		free(content);
		free(zero_str);
		return (ret);
	}
	return ((char *)content);
}
