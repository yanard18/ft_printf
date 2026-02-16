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

/*
int	main(void)
{
	char *s;

	ft_putstr_fd("\n", 1);
	ft_printf("%3d", 1);
#include <stdio.h>
	printf("<%3d>", 1);

	return (0);
}
*/
