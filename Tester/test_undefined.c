#include "ft_printf_test.h"
#include "../ft_printf.h"

void test_undefined()
{
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %d%", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC % MORE");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC % MORE%");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %MORE%");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %MORE %");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %MORE%%");
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %MORE%d", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %MORE%d%", 42);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %", 1);
	TEST_STDOUT_FUNC(printf, ft_printf, "%t", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%M", 42);;
	TEST_STDOUT_FUNC(printf, ft_printf, "%L", 42);;
}

REGISTER_TEST(test_undefined)
