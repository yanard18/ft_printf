#include "ft_printf_test.h"
#include <limits.h>
#include "ft_printf.h"

void test_mendatory()
{
	printf("\ntest basic:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "");
	TEST_STDOUT_FUNC(printf, ft_printf, "A");
	TEST_STDOUT_FUNC(printf, ft_printf, "AB");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d", 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC \042", 42);

	printf("\ntest unfinished token sepcifier:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "%");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %", 42);
	
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%%%");
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%");
	TEST_STDOUT_FUNC(printf, ft_printf, "% %%");
	TEST_STDOUT_FUNC(printf, ft_printf, "% % %");

	printf("\ntest duplicate flags:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%++d", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "%+++d", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%  d", 42);

	printf("\ntest wihtout %%:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC 5");
	TEST_STDOUT_FUNC(printf, ft_printf, "AB");
	TEST_STDOUT_FUNC(printf, ft_printf, "A");
	TEST_STDOUT_FUNC(printf, ft_printf, "AB\0C");
	TEST_STDOUT_FUNC(printf, ft_printf, "AB\nC");
	TEST_STDOUT_FUNC(printf, ft_printf, "   AB C   ");
	TEST_STDOUT_FUNC(printf, ft_printf, "");

	printf("\ntest %%d:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", 0);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", -1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", INT_MAX);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", INT_MIN);;
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC: %d", -1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "X:%d Y:%d", -1, 42);;

	printf("\ntest %%i:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%i", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%d", 0x2a);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%i", INT_MIN);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%i", INT_MAX);;

	printf("\ntest %%u:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%u", 0);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%u", 1); // -1 wraps to UINT_MAX;
	TEST_STDOUT_FUNC(printf, ft_printf, "%u", -1); // -1 wraps to UINT_MAX;


	printf("\ntest %%s:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%s", "ABC");;
	TEST_STDOUT_FUNC(printf, ft_printf, "Hello %s", "ABC");;
	TEST_STDOUT_FUNC(printf, ft_printf, "%s%s", "ABC", "abc");;
	TEST_STDOUT_FUNC(printf, ft_printf, "%s", "");;
	TEST_STDOUT_FUNC(printf, ft_printf, "%s", "AB\0C");;

	printf("\ntest %%c:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%c", 'a');
	TEST_STDOUT_FUNC(printf, ft_printf, "%c%c", 'a','b');
	TEST_STDOUT_FUNC(printf, ft_printf, "c", 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %c%s", '\0', "Hello!");

	printf("\ntest %%x:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%x", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%x", 0);;

	printf("\ntest %%X:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%X", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%X", 0);;
	

	{
		printf("\ntest %%p:\n");
		int x = 0;
		TEST_STDOUT_FUNC(printf, ft_printf, "%p", &x);;
	}

	{
		printf("\ntest (nil):\n");
		TEST_STDOUT_FUNC(printf, ft_printf, "%d", 0); // expect 0;
		TEST_STDOUT_FUNC(printf, ft_printf, "%x", 0); // expect 0;
		TEST_STDOUT_FUNC(printf, ft_printf, "%s", 0); // expect (null);
		TEST_STDOUT_FUNC(printf, ft_printf, "%p", 0); // expect (nil);
	}

	printf("\ntest %%%%:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%%");;
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%d%%%s", 42, "abc");;
}

REGISTER_TEST(test_mendatory)
