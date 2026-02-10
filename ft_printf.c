#include <stdio.h>
#include <stdarg.h>

int	ft_printf(int n, ...)
{
	va_list args;
	va_start(args, n); // init
	for (int i = 0; i < n; i++) 
	{
		printf("%d ", va_arg(args, int)); // pop
		fflush(stdout);
	}
	printf("\n");
	va_end(args); // free
} 

int	main(void)
{
	ft_printf(4, 10, 20, 40, 44);
}
