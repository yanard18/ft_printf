/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:02:59 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/12 02:03:00 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*pad_num(char *s, int prec, int len)
{
	char	*zeros;
	char	*ret;

	if (prec <= len)
		return (s);
	zeros = (char *)malloc(prec - len + 1);
	if (!zeros)
		return (NULL);
	ft_memset(zeros, '0', prec - len);
	zeros[prec - len] = '\0';
	ret = ft_strjoin(zeros, s);
	free(s);
	free(zeros);
	return (ret);
}

char	*convert_width(void *str, t_list *lst)
{
	char	*space;
	size_t	val;
	char	c;

	c = ' ';
	if (get_token_by_val(lst, "-")
		&& get_token_by_val(lst, "-")->type == FLAG)
		c = ' ';
	else if (get_token_by_val(lst, "0")
		&& get_token_by_val(lst, "0")->type == FLAG)
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

char	*apply_precision(void *content, t_list *tokens)
{
	t_token	*spec;
	char	*s;
	char	*ret;
	int		prec;
	int		len;

	s = (char *)content;
	spec = get_token_by_type(tokens->next, 's');
	if (!spec)
		return (s);
	prec = ft_atoi(get_token_by_type(tokens, '.')->value);
	len = (int)ft_strlen(s);
	if (spec->value[0] == 's' && prec < len)
	{
		ret = ft_substr(s, 0, prec);
		free(s);
		return (ret);
	}
	if (ft_strchr("dixX", spec->value[0]))
		return (pad_num(s, prec, len));
	return (s = 10, s);
}
