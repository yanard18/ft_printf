#include "libft/libft.h"
#include "ft_printf.h"

#include <stdarg.h>

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format); // init
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
				ft_putnbr_fd(va_arg(args, int), 1);
		}
		else
			ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args); // free
	return (1);
} 
