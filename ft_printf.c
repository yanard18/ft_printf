#include "libft/libft.h"
#include "ft_printf.h"

char	*apply_plus_flag(char *s)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	free(s);
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*res;
	int		has_plus_flag = 0;

	va_start(args, format); // init
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			// read flags
			if (*format == '+')
			{
				has_plus_flag = 1;
				format++;
			}
			// add functions for each flag into linked list
			// apply field width
			// check precision
			// apply precision minimum digits

			if (*format == 'd')
				res = ft_itoa(va_arg(args, int));

			if (has_plus_flag)
				res = apply_plus_flag(res);
			ft_putstr_fd(res, 1);

		}
		else
		{
			ft_putchar_fd(*format, 1);
		}
		format++;
	}

	
	va_end(args); // free
	return (1);
} 

/*
int	main(void)
{
	ft_printf("ABC");
	return (0);
}
*/
