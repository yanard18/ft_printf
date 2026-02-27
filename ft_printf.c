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

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	len;
	int  	token_len;
	t_token *token_buf;

	if (!format)
		return (-1);
    len = 0;
    va_start(args, format);
    while (*format)
		{
			if (*format == '%')
				{
					token_buf = init_token_buf();
					token_len = read_token(&format, args, token_buf);
					free(token_buf);
					if (token_len == -1)
						return (-1);
					len += token_len;
					continue ;
				}
			ft_putchar_fd(*format, 1);
			format++;
			len++;
		}
	va_end(args);
	return (len);
} 
