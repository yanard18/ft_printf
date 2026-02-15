#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			read_token(&format);
		}
		ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (1);
} 

int	main(void)
{
	ft_printf("ABC %d", 1);
	return (0);
}
