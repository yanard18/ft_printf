#include "libft/libft.h"

int	ft_printf(const char *format, ...)
{
	/*
	va_list args;
	va_start(args, n); // init
	for (int i = 0; i < n; i++) 
		printf("%d ", va_arg(args, int)); // pop
	printf("\n");
	va_end(args); // free
	*/
	while (*format)
	{
		ft_putchar_fd(*format, 1);
		format++;
	}
	return (1);
} 
