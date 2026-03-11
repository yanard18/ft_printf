/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:23:56 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 20:27:48 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_token	*init_token_buf(void)
{
	t_token	*buf;

	buf = (t_token *)malloc(sizeof(t_token) * 18);
	buf[0] = (t_token){'f', "#", 10, convert_hash};
	buf[1] = (t_token){'f', "-", 11, NULL};
	buf[2] = (t_token){'f', "0", 11, NULL};
	buf[3] = (t_token){'f', " ", 12, convert_space};
	buf[4] = (t_token){'f', "+", 13, convert_plus};
	buf[5] = (t_token){'w', NULL, 20, convert_width};
	buf[6] = (t_token){'.', NULL, 5, apply_precision};
	buf[7] = (t_token){'s', "c", 99, convert_d};
	buf[8] = (t_token){'s', "s", 99, convert_s};
	buf[9] = (t_token){'s', "p", 99, convert_p};
	buf[10] = (t_token){'s', "d", 99, convert_d};
	buf[11] = (t_token){'s', "i", 99, convert_d};
	buf[12] = (t_token){'s', "u", 99, convert_u};
	buf[13] = (t_token){'s', "x", 99, convert_x};
	buf[14] = (t_token){'s', "X", 99, convert_bigx};
	buf[15] = (t_token){'s', "%", 1, NULL};
	buf[16] = (t_token){'+', NULL, 0, NULL};
	buf[17] = (t_token){'0', NULL, 0, NULL};
	return (buf);
}

static	int	flush(char *res, va_list args, t_token *token_buf)
{
	int	len;
	int	downgraded;

	downgraded = token_buf[16].type == DOWNGRADE;
	free(token_buf);
	va_end(args);
	if (res)
	{
		ft_putstr_fd(res, 1);
		len = ft_strlen(res);
		free(res);
		if (downgraded)
			return (-1);
		return (len);
	}
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_token	*token_buf;
	char	*res;

	if (!format)
		return (-1);
	res = ft_strdup("");
	token_buf = init_token_buf();
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			res = strjoin_safe(res, read_token(&format, args, token_buf));
		else
			res = strjoin_safe(res, move_str_to_chr(&format, '%'));
	}
	return (flush(res, args, token_buf));
}
