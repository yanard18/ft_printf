#include "ft_printf_test.h"

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
	return (0);
}
