#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
    size_t	len;
	int  token_len;

	if (!format)
	return (-1);
    len = 0;
    va_start(args, format);
    while (*format)
    {
		if (*format == '%')
		{
			token_len =read_token(&format, args);
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
