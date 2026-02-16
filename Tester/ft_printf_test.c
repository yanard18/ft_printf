#include "ft_printf_test.h"
#include "../ft_printf.h"

int	main(void)
{
	/* Ideas for interface */
	//TEST("ABC", GET_STDOUT(ft_printf("ABC"))
	//TEST(printf(...), ft_printf(...))
	INIT
	dprintf(saved_stdout, "\ntest wihtout %%:\n");
	TEST("ABC", ft_printf("ABC"))
	TEST("ABC 5", ft_printf("ABC 5"))
	TEST("AB", ft_printf("AB"))
	TEST("A", ft_printf("A"))
	TEST("AB\0", ft_printf("AB\0C"))
	TEST("AB\nC", ft_printf("AB\nC"))
	TEST("   AB C   ", ft_printf("   AB C   "))
	TEST("", ft_printf(""))
	dprintf(saved_stdout, "\ntest %%d:\n");
	TEST("42", ft_printf("%d", 42));
	TEST("0", ft_printf("%d", 0));
	TEST("-1", ft_printf("%d", -1));
	TEST("ABC: -1", ft_printf("ABC: %d", -1));
	TEST("X:-1 Y:42", ft_printf("X:%d Y:%d", -1, 42));

	dprintf(saved_stdout, "\ntest %%s:\n");
	TEST("ABC", ft_printf("%s", "ABC"));
	dprintf(saved_stdout, "\ntest '+' flag:\n");
	TEST("+42", ft_printf("%+d", 42));
	TEST("+0", ft_printf("%+d", 0));
	TEST("-42", ft_printf("%+d", -42));
	TEST("+ABC", ft_printf("%+s", "ABC"));
	TEARDOWN
	return (0);
}
