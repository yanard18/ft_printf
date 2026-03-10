#include "ft_printf.h"

static t_token *init_token_buf()
{
	t_token *buf;

	buf = (t_token *)malloc(sizeof(t_token) * 17);
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
	buf[16] = (t_token){'0', NULL, 0, NULL};
	return (buf);
}

static char *move_str_to_chr(const char **format, char c)
{
	const char *format_start;

	if (*format == NULL)
		return (NULL);
	format_start = *format;
	while (**format)
		{
			(*format)++;
			if (**format == c)
					break ;
		}
	return (ft_substr(format_start, 0, *format - format_start));
}

static char *strjoin_safe(char *s1, char *s2)
{
	char *res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static int flush(char *res, va_list args, int should_fail)
{
	int	len;

	va_end(args);
	if (should_fail == 1)
		return (-1);
	else if (res)
	{
		ft_putstr_fd(res, 1);
		len = ft_strlen(res);
		free(res);
		return (len);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_token *token_buf;
	char *res;
	int len;

	if (!format)
		return (-1);
	res = ft_strdup("");
    va_start(args, format);
    while (*format)
		{
			if (*format == '%')
				{
					token_buf = init_token_buf();
					res = strjoin_safe(res, read_token(&format, args, token_buf));
					free(token_buf);
					if (!res)
						return (flush(res, args, 1));
					continue ;
				}
			res = strjoin_safe(res, move_str_to_chr(&format, '%'));
		}
	return (flush(res, args, 0));
} 
