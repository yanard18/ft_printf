#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
    va_list	args;
    size_t	len;

    len = 0;
    va_start(args, format);
    while (*format)
    {
		if (*format == '%')
		{
			len += read_token(&format, args);
			continue ;
		}
		ft_putchar_fd(*format, 1);
		format++;
		len++;
    }
    va_end(args);
    return (len);
} 
