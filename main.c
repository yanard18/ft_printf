#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	ft_printf("<%+#-8.4x>%%%s", 42, "ABC");
	return (0);
}
