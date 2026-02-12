#include "printf_tester.h"
#include "../ft_printf.h"

int	main(void)
{
	INIT
	dprintf(saved_stdout, "print_as_it_is_when_no_special_char:\n");
	TEST("ABC", ft_printf("ABC"))
	TEST("AB", ft_printf("AB"))
	TEST("A", ft_printf("A"))
	TEST("AB\0", ft_printf("AB\0C"))
	TEST("AB\nC", ft_printf("AB\nC"))
	TEST("   AB C   ", ft_printf("   AB C   "))
	TEST("", ft_printf(""))
	dprintf(saved_stdout, " %-s \n", "XXX");
	dprintf(saved_stdout, "print_as_it_is_when_no_special_char:\n");
	TEST_RETURN(1, ft_printf("ABC"));
	TEARDOWN
	return (0);
}
