#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			read_token(&format, args);
			continue ;
		}
		ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (1);
} 

int	main(void)
{
	char *s;

	s = "X:%d Y:%+d";
	ft_printf(s, -1, 42);
	return (0);
}
