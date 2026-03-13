#include "ft_printf_test.h"
#include "ft_printf.h"

void test_c()
{
	printf("\ntest %%c:\n");
	TEST_STDOUT_FUNC(printf, ft_printf, "%c", 'a');
	TEST_STDOUT_FUNC(printf, ft_printf, "%c%c", 'a','b');
	TEST_STDOUT_FUNC(printf, ft_printf, "c", 0);
	TEST_STDOUT_FUNC(printf, ft_printf, "ABC %c%s", '\0', "Hello!");
}

REGISTER_TEST(test_c)
