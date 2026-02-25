#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int x = 0;
	printf("printf: %p\n", &x);
	fflush(stdout);
	ft_printf("ft_printf: %p", &x);
	return (0);
}
