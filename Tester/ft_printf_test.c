#include "ft_printf_test.h"
#include "../ft_printf.h"
#include <limits.h>

t_test *g_test_lst = NULL;

void register_test(const char *name, void (*func)(void)) {
    t_test *new_test = malloc(sizeof(t_test));
	if (!new_test)
		return ;
    new_test->name = name;
    new_test->func = func;
    new_test->next = g_test_lst;
    g_test_lst = new_test;
}


int	main(void)
{
	while (g_test_lst)
		{
			g_test_lst->func();
			t_test *next_test = g_test_lst->next;
			free(g_test_lst);
			g_test_lst = next_test;
		}
	printf("\ntest basic:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "");
	TEST_STDOUT_FUNC(printf, ft_printf, "A");
	TEST_STDOUT_FUNC(printf, ft_printf, "AB");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d", 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %#x", 42);

	printf("\ntest unfinished token sepcifier:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "%");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %", 1);
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


	{
		printf("\ntest token order:\n");
		TEST_STDOUT_FUNC(printf, ft_printf, "%#-3.2x", 42);;
	}

	printf("\ntest %%%%:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%%");;
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%%%d%%%s", 42, "abc");;

	printf("\ntest '+' flag:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%+d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%+i", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%+u", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%+x", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%+d", 0);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%+d", -42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%+s", "ABC"); // undefined behaviour;

	printf("\ntest '0' flag:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%00d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%01d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%02d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%03d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%05d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%0-5d", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%-05d", 42);;

	printf("\ntest field width:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "<%0d>", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "<%1d>", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "<%2d>", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "<%3d>", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "<%-3d>", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "<%5s>", "abc");;

	printf("\ntest # flag:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%#x", 0);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%#x", 1);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%#x", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%#X", 42);;

	{
		printf("\ntest . precision:\n");
		TEST_STDOUT_FUNC(printf, ft_printf, "%.d", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "%.0d", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "%.1d", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "%.2d", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "%.3d", 42);;
	}

	{
		printf("\ntest undefined token values:\n");
		TEST_STDOUT_FUNC(printf, ft_printf, "%t", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "%L", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "%", 42);;
	}

	{
		printf("\ntest combinational:\n");
		TEST_STDOUT_FUNC(printf, ft_printf, "%s %d", "NUM", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "<%#-10.6x>", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "<%+#10.6x>", 42);;
		TEST_STDOUT_FUNC(printf, ft_printf, "<%+#-8.4x>%%%s", 42, "ABC");;
		TEST_STDOUT_FUNC(printf, ft_printf, "<%-+8.6d>", 42);;
	}
	return (0);
}
