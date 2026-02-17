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
	TEST("Hello ABC", ft_printf("Hello %s", "ABC"));
	TEST("ABCabc", ft_printf("%s%s", "ABC", "abc"));
	TEST("", ft_printf("%s", ""));
	TEST("AB", ft_printf("%s", "AB\0C"));
	dprintf(saved_stdout, "\ntest %%x:\n");
	TEST("2a", ft_printf("%x", 42));

	dprintf(saved_stdout, "\ntest %%%%:\n");
	TEST("%", ft_printf("%%"));
	TEST("%42", ft_printf("%%%d", 42));
	TEST("%42%abc", ft_printf("%%%d%%%s", 42, "abc"));

	dprintf(saved_stdout, "\ntest '+' flag:\n");
	TEST("+42", ft_printf("%+d", 42));
	TEST("+0", ft_printf("%+d", 0));
	TEST("-42", ft_printf("%+d", -42));
	TEST("+ABC", ft_printf("%+s", "ABC")); // undefined behaviour
	TEST("+2a", ft_printf("%+x", 42));
	TEST("-2a", ft_printf("%+x", -42));

	dprintf(saved_stdout, "\ntest field width:\n");
	TEST("<1>", ft_printf("<%0d>", 1));
	TEST("<1>", ft_printf("<%1d>", 1));
	TEST("< 1>", ft_printf("<%2d>", 1));
	TEST("<  1>", ft_printf("<%3d>", 1));
	TEST("<1  >", ft_printf("<%-3d>", 1));

	dprintf(saved_stdout, "\ntest combinational:\n");
	TEST("NUM 42", ft_printf("%s %d", "NUM", 42));
	TEST("<  abc>", ft_printf("<%5s>", "abc"));

	dprintf(saved_stdout, "\ntest # flag:\n");
	TEST("0x2a", ft_printf("%#x", 42));

	dprintf(saved_stdout, "\ntest . precision:\n");
	TEST("42", ft_printf("%.0d", 42));
	TEST("42", ft_printf("%.1d", 42));
	TEST("42", ft_printf("%.2d", 42));
	TEST("042", ft_printf("%.3d", 42));
	TEARDOWN
	return (0);
}
