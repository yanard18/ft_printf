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

	s = "ABC %#+123.52d";
	ft_putstr_fd("format: ", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	ft_printf(s, 1);
	return (0);
}
