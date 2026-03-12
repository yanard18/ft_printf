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

static char	*apply_pad(char *s, int p_len, char c, int align_r)
{
	char	*pad;
	char	*ret;
	int		is_neg;

	if (p_len <= 0)
		return (s);
	pad = (char *)malloc(p_len + 1);
	if (!pad)
		return (NULL);
	ft_memset(pad, c, p_len);
	pad[p_len] = '\0';
	is_neg = (c == '0' && s[0] == '-');
	if (is_neg)
		s[0] = '0';
	if (align_r)
		ret = ft_strjoin(pad, s);
	else
		ret = ft_strjoin(s, pad);
	if (is_neg)
		ret[0] = '-';
	free(s);
	free(pad);
	return (ret);
}

char	*convert_width(void *str, t_list *lst)
{
	int		val;
	char	c;
	int		align_r;
	t_token	*tok;

	c = ' ';
	align_r = 1;
	tok = get_token_by_val(lst, "-");
	if (tok && tok->type == FLAG)
		align_r = 0;
	else
	{
		tok = get_token_by_val(lst, "0");
		if (tok && tok->type == FLAG)
			c = '0';
	}
	val = ft_atoi(get_token_by_type(lst, 'w')->value);
	return (apply_pad((char *)str, val - (int)ft_strlen(str), c, align_r));
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
		return (apply_pad(s, prec - len + (s[0] == '-'), '0', 1));
	return (s);
}
