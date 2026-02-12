#include "printf_tester.h"
#include "../ft_printf.h"

int	main(void)
{
	INIT
	TEST("ABC", ft_printf("ABC"))
	TEARDOWN
	return (0);
}
