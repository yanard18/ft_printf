/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_padding_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:02:59 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/13 23:01:49 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	fix_prefix(char *s, char *ret, int p_len)
{
	if (s[0] == '-' || s[0] == '+' || s[0] == ' ')
	{
		ret[0] = s[0];
		ret[p_len] = '0';
	}
	else if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
	{
		ret[1] = s[1];
		ret[p_len + 1] = '0';
	}
}

static char	*apply_pad(char *s, int p_len, char c, int align_r)
{
	char	*pad;
	char	*ret;

	if (p_len <= 0)
		return (s);
	pad = (char *)malloc(p_len + 1);
	if (!pad)
		return (NULL);
	ft_memset(pad, c, p_len);
	pad[p_len] = '\0';
	if (align_r)
		ret = ft_strjoin(pad, s);
	else
		ret = ft_strjoin(s, pad);
	if (align_r && c == '0')
		fix_prefix(s, ret, p_len);
	free(s);
	free(pad);
	return (ret);
}

static char	*handle_num_prec(char *s, int prec)
{
	int	len;

	len = (int)ft_strlen(s);
	if (prec == 0 && s[0] == '0' && len == 1)
	{
		free(s);
		return (ft_strdup(""));
	}
	return (apply_pad(s, prec - len + (s[0] == '-'), '0', 1));
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
		if (tok && tok->type == FLAG && !get_token_by_type(lst, '.'))
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

	s = (char *)content;
	spec = get_token_by_type(tokens, 's');
	if (!spec)
		return (s);
	prec = ft_atoi(get_token_by_type(tokens, '.')->value);
	if (spec->value[0] == 's' && prec < (int)ft_strlen(s))
	{
		ret = ft_substr(s, 0, prec);
		free(s);
		return (ret);
	}
	if (ft_strchr("diuxX", spec->value[0]))
		return (handle_num_prec(s, prec));
	return (s);
}
