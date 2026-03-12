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
	if (!buf)
		return (NULL);
	buf[7] = (t_token){'s', "c", 10, convert_c};
	buf[8] = (t_token){'s', "s", 10, convert_s};
	buf[9] = (t_token){'s', "p", 10, convert_p};
	buf[10] = (t_token){'s', "d", 10, convert_d};
	buf[11] = (t_token){'s', "i", 10, convert_d};
	buf[12] = (t_token){'s', "u", 10, convert_u};
	buf[13] = (t_token){'s', "x", 10, convert_x};
	buf[14] = (t_token){'s', "X", 10, convert_bigx};
	buf[15] = (t_token){'s', "%", 10, NULL};
	buf[6] = (t_token){'.', NULL, 20, apply_precision};
	buf[0] = (t_token){'f', "#", 30, convert_hash};
	buf[4] = (t_token){'f', "+", 30, convert_plus};
	buf[3] = (t_token){'f', " ", 31, convert_space};
	buf[5] = (t_token){'w', NULL, 40, convert_width};
	buf[1] = (t_token){'f', "-", 0, NULL};
	buf[2] = (t_token){'f', "0", 0, NULL};
	buf[16] = (t_token){'+', NULL, 0, NULL};
	buf[17] = (t_token){'0', NULL, 0, NULL}; 
	return (buf);
}


static    int    flush(char *res, va_list args, t_token *token_buf)
{
    int    len;
    int    downgraded;
    int    i;

    downgraded = token_buf[16].type == DOWNGRADE;
    free(token_buf);
    va_end(args);
    if (res)
    {
        len = ft_strlen(res);
        i = 0;
        while (i < len)
        {
            if (res[i] == '\1')
                write(1, "\0", 1);
            else
                write(1, &res[i], 1);
            i++;
        }
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
