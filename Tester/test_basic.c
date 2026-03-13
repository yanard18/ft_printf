#include "ft_printf_test.h"
#include "ft_printf.h"

void test_basic()
{
	printf("\ntest basic:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "");
	TEST_STDOUT_FUNC(printf, ft_printf, "A");
	TEST_STDOUT_FUNC(printf, ft_printf, "AB");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d", 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC \042", 42);
}

REGISTER_TEST(test_basic)
