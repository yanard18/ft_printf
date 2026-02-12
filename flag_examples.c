#include <stdio.h>

int	main(void)
{
	 int x = 345;
    const char * y = "monkeys";

    /* Demonstrate with numbers. */
    printf ("<%d> is not justified.\n", x);
    printf ("<%5d> is right-justified.\n", x);
    printf ("<%-5d> The minus sign makes it left-justified.\n", x);
    /* Demonstrate with strings. */
    printf ("'%s' is not justified.\n", y);
    printf ("'%10s' is right-justified.\n", y);
    printf ("'%-10s' is left-justified using a minus sign.\n", y);

    return 0;
}
