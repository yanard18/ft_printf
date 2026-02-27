#include "ft_printf_test.h"
#include "../ft_printf.h"
#include <limits.h>

int	main(void)
{
	dprintf(saved_stdout, "\ntest basic:\n");
	TEST_STDOUT_FUNC(printf(""), ft_printf(""))
	TEST_STDOUT_FUNC(printf("A"), ft_printf("A"))
	TEST_STDOUT_FUNC(printf("AB"), ft_printf("AB"))
	TEST_STDOUT_FUNC(printf("ABC"), ft_printf("ABC"))
	TEST_STDOUT_FUNC(printf("ABC %d", 0), ft_printf("ABC %d", 0))
	TEST_STDOUT_FUNC(printf("ABC %d", 42), ft_printf("ABC %d", 42))
	TEST_STDOUT_FUNC(printf("ABC %#x", 42), ft_printf("ABC %#x", 42))

	dprintf(saved_stdout, "\ntest unfinished token sepcifier:\n");
	TEST_STDOUT_FUNC(printf(0), ft_printf(0))
	TEST_STDOUT_FUNC(printf("%"), ft_printf("%"))
	TEST_STDOUT_FUNC(printf("ABC %"), ft_printf("ABC %"))
	TEST_STDOUT_FUNC(printf("ABC %", 1), ft_printf("ABC %", 1))
	TEST_STDOUT_FUNC(printf("%%%%%"), ft_printf("%%%%%"))
	TEST_STDOUT_FUNC(printf("%%%"), ft_printf("%%%"))
	TEST_STDOUT_FUNC(printf("% %%"), ft_printf("% %%"))
	TEST_STDOUT_FUNC(printf("% % %"), ft_printf("% % %"))

	dprintf(saved_stdout, "\ntest duplicate flags:\n");
	TEST_STDOUT_FUNC(printf("%++d", 42), ft_printf("%++d", 42))
	TEST_STDOUT_FUNC(printf("%+++d", 42), ft_printf("%+++d", 42))
	TEST_STDOUT_FUNC(printf("%%%  d", 42), ft_printf("%%%  d", 42))

	dprintf(saved_stdout, "\ntest wihtout %%:\n");
	TEST_STDOUT_FUNC(printf("ABC"), ft_printf("ABC"))
	TEST_STDOUT_FUNC(printf("ABC 5"), ft_printf("ABC 5"))
	TEST_STDOUT_FUNC(printf("AB"), ft_printf("AB"))
	TEST_STDOUT_FUNC(printf("A"), ft_printf("A"))
	TEST_STDOUT_FUNC(printf("AB\0C"), ft_printf("AB\0C"))
	TEST_STDOUT_FUNC(printf("AB\nC"), ft_printf("AB\nC"))
	TEST_STDOUT_FUNC(printf("   AB C   "), ft_printf("   AB C   "))
	TEST_STDOUT_FUNC(printf(""), ft_printf(""))

	dprintf(saved_stdout, "\ntest %%d:\n");
	TEST_STDOUT_FUNC(printf("%d", 0), ft_printf("%d", 0));
	TEST_STDOUT_FUNC(printf("%d", 1), ft_printf("%d", 1));
	TEST_STDOUT_FUNC(printf("%d", -1), ft_printf("%d", -1));
	TEST_STDOUT_FUNC(printf("%d", 42), ft_printf("%d", 42));
	TEST_STDOUT_FUNC(printf("%d", INT_MAX), ft_printf("%d", INT_MAX));
	TEST_STDOUT_FUNC(printf("%d", INT_MIN), ft_printf("%d", INT_MIN));
	TEST_STDOUT_FUNC(printf("ABC: %d", -1), ft_printf("ABC: %d", -1));
	TEST_STDOUT_FUNC(printf("X:%d Y:%d", -1, 42), ft_printf("X:%d Y:%d", -1, 42));

	dprintf(saved_stdout, "\ntest %%i:\n");
	TEST_STDOUT_FUNC(printf("%i", 42), ft_printf("%i", 42));
	TEST_STDOUT_FUNC(printf("%d", 0x2a), ft_printf("%d", 0x2a));
	TEST_STDOUT_FUNC(printf("%i", INT_MIN), ft_printf("%i", INT_MIN));
	TEST_STDOUT_FUNC(printf("%i", INT_MAX), ft_printf("%i", INT_MAX));

	dprintf(saved_stdout, "\ntest %%u:\n");
	TEST_STDOUT_FUNC(printf("%u", 0), ft_printf("%u", 0));
	TEST_STDOUT_FUNC(printf("%u", 1), ft_printf("%u", 1)); // -1 wraps to UINT_MAX
	TEST_STDOUT_FUNC(printf("%u", -1), ft_printf("%u", -1)); // -1 wraps to UINT_MAX


	dprintf(saved_stdout, "\ntest %%s:\n");
	TEST_STDOUT_FUNC(printf("%s", "ABC"), ft_printf("%s", "ABC"));
	TEST_STDOUT_FUNC(printf("Hello %s", "ABC"), ft_printf("Hello %s", "ABC"));
	TEST_STDOUT_FUNC(printf("%s%s", "ABC", "abc"), ft_printf("%s%s", "ABC", "abc"));
	TEST_STDOUT_FUNC(printf("%s", ""), ft_printf("%s", ""));
	TEST_STDOUT_FUNC(printf("%s", "AB\0C"), ft_printf("%s", "AB\0C"));

	/* negative values for %x and %X are undefined behaviour */
	dprintf(saved_stdout, "\ntest %%x:\n");
	TEST_STDOUT_FUNC(printf("%x", 42), ft_printf("%x", 42));
	TEST_STDOUT_FUNC(printf("%x", 0), ft_printf("%x", 0));

	dprintf(saved_stdout, "\ntest %%X:\n");
	TEST_STDOUT_FUNC(printf("%X", 42), ft_printf("%X", 42));
	TEST_STDOUT_FUNC(printf("%X", 0), ft_printf("%X", 0));
	

	{
		dprintf(saved_stdout, "\ntest %%p:\n");
		int x = 0;
		TEST_STDOUT_FUNC(printf("%p", &x), ft_printf("%p", &x));
	}

	{
		dprintf(saved_stdout, "\ntest (nil):\n");
		TEST_STDOUT_FUNC(printf("%d", 0), ft_printf("%d", 0)); // expect 0
		TEST_STDOUT_FUNC(printf("%x", 0), ft_printf("%x", 0)); // expect 0
		TEST_STDOUT_FUNC(printf("%s", 0), ft_printf("%s", 0)); // expect (null)
		TEST_STDOUT_FUNC(printf("%p", 0), ft_printf("%p", 0)); // expect (nil)
	}


	{
		dprintf(saved_stdout, "\ntest token order:\n");
		TEST_STDOUT_FUNC(printf("%#-3.2x", 42), ft_printf("%#-3.2x", 42));
	}

	dprintf(saved_stdout, "\ntest %%%%:\n");
	TEST_STDOUT_FUNC(printf("%%"), ft_printf("%%"));
	TEST_STDOUT_FUNC(printf("%%%d", 42), ft_printf("%%%d", 42));
	TEST_STDOUT_FUNC(printf("%%%d%%%s", 42, "abc"), ft_printf("%%%d%%%s", 42, "abc"));

	dprintf(saved_stdout, "\ntest '+' flag:\n");
	TEST_STDOUT_FUNC(printf("%+d", 42), ft_printf("%+d", 42));
	TEST_STDOUT_FUNC(printf("%+i", 42), ft_printf("%+i", 42));
	TEST_STDOUT_FUNC(printf("%+u", 42), ft_printf("%+u", 42));
	TEST_STDOUT_FUNC(printf("%+x", 42), ft_printf("%+x", 42));
	TEST_STDOUT_FUNC(printf("%+d", 0), ft_printf("%+d", 0));
	TEST_STDOUT_FUNC(printf("%+d", -42), ft_printf("%+d", -42));
	TEST_STDOUT_FUNC(printf("%+s", "ABC"), ft_printf("%+s", "ABC")); // undefined behaviour

	dprintf(saved_stdout, "\ntest '0' flag:\n");
	TEST_STDOUT_FUNC(printf("%00d", 42), ft_printf("%00d", 42));
	TEST_STDOUT_FUNC(printf("%01d", 42), ft_printf("%01d", 42));
	TEST_STDOUT_FUNC(printf("%02d", 42), ft_printf("%02d", 42));
	TEST_STDOUT_FUNC(printf("%03d", 42), ft_printf("%03d", 42));
	TEST_STDOUT_FUNC(printf("%05d", 42), ft_printf("%05d", 42));
	TEST_STDOUT_FUNC(printf("%0-5d", 42), ft_printf("%0-5d", 42));
	TEST_STDOUT_FUNC(printf("%-05d", 42), ft_printf("%-05d", 42));

	dprintf(saved_stdout, "\ntest field width:\n");
	TEST_STDOUT_FUNC(printf("<%0d>", 1), ft_printf("<%0d>", 1));
	TEST_STDOUT_FUNC(printf("<%1d>", 1), ft_printf("<%1d>", 1));
	TEST_STDOUT_FUNC(printf("<%2d>", 1), ft_printf("<%2d>", 1));
	TEST_STDOUT_FUNC(printf("<%3d>", 1), ft_printf("<%3d>", 1));
	TEST_STDOUT_FUNC(printf("<%-3d>", 1), ft_printf("<%-3d>", 1));
	TEST_STDOUT_FUNC(printf("<%5s>", "abc"), ft_printf("<%5s>", "abc"));

	dprintf(saved_stdout, "\ntest # flag:\n");
	TEST_STDOUT_FUNC(printf("%#x", 0), ft_printf("%#x", 0));
	TEST_STDOUT_FUNC(printf("%#x", 1), ft_printf("%#x", 1));
	TEST_STDOUT_FUNC(printf("%#x", 42), ft_printf("%#x", 42));
	TEST_STDOUT_FUNC(printf("%#X", 42), ft_printf("%#X", 42));

	{
		dprintf(saved_stdout, "\ntest . precision:\n");
		TEST_STDOUT_FUNC(printf("%.d", 42), ft_printf("%.d", 42));
		TEST_STDOUT_FUNC(printf("%.0d", 42), ft_printf("%.0d", 42));
		TEST_STDOUT_FUNC(printf("%.1d", 42), ft_printf("%.1d", 42));
		TEST_STDOUT_FUNC(printf("%.2d", 42), ft_printf("%.2d", 42));
		TEST_STDOUT_FUNC(printf("%.3d", 42), ft_printf("%.3d", 42));
	}

	{
		dprintf(saved_stdout, "\ntest undefined token values:\n");
		TEST_STDOUT_FUNC(printf("%t", 42), ft_printf("%t", 42));
		TEST_STDOUT_FUNC(printf("%L", 42), ft_printf("%L", 42));
		TEST_STDOUT_FUNC(printf("%", 42), ft_printf("%", 42));
	}

	{
		dprintf(saved_stdout, "\ntest combinational:\n");
		TEST_STDOUT_FUNC(printf("%s %d", "NUM", 42), ft_printf("%s %d", "NUM", 42));
		TEST_STDOUT_FUNC(printf("<%#-10.6x>", 42), ft_printf("<%#-10.6x>", 42));
		TEST_STDOUT_FUNC(printf("<%+#10.6x>", 42), ft_printf("<%+#10.6x>", 42));
		TEST_STDOUT_FUNC(printf("<%+#-8.4x>%%%s", 42, "ABC"), ft_printf("<%+#-8.4x>%%%s", 42, "ABC"));
		TEST_STDOUT_FUNC(printf("<%-+8.6d>", 42), ft_printf("<%-+8.6d>", 42));
	}
	return (0);
}
