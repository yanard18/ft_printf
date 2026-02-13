#include <stdio.h>

int	main(void)
{
	int x = 345;
    const char * y = "monkeys";

	/*test*/
    /* Demonstrate with numbers. */
    printf ("<%d> is not justified.\n", x);
    printf ("<%5d> is right-justified.\n", x);
    printf ("<%-5d> The minus sign makes it left-justified.\n", x);
    printf ("<%+d> The plus sign makes it left-justified.\n", -42);
    printf ("<%05d> The 0 flag fill padding with 0s\n", 42);
    printf ("<%+d> The plus sign display '+' prefix on positive numbers\n", 42);
    printf ("<% d> ' ' flag makes positive numbers to start with space\n", 42);
	/* # flag for alternative values of numbers */
    printf ("<%#o> #o.\n", x);
    printf ("<%#x> #x.\n", x);
    printf ("<%#X> #X (capitalize latters).\n", x);
    printf ("<%#e> #e.\n", x);
    printf ("<%#f> #f.\n", x);
    printf ("<%#g> #g.\n", x);
    printf ("<%#G> #G.\n", x);
    printf ("<%d> is not justified.\n", x);
    printf ("<%d> is not justified.\n", x);
    printf ("<%d> is not justified.\n", x);
    /* Demonstrate with strings. */
    printf ("'%s' is not justified.\n", y);
    printf ("'%10s' is right-justified.\n", y);
    printf ("'%-10s' is left-justified using a minus sign.\n", y);

    return 0;
}
