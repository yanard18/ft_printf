#include <stdio.h>

int	main(void)
{
	int x = 345;
	float z = 123.45;
    const char * y = "monkeys";

	/* syntax: */
	/* % (flags) (width) (precision) (length) (conversion specifier) */
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
    printf ("<%#e> #e.\n", z); // expect double
    printf ("<%#f> #f.\n", z); // expect double
    printf ("<%#g> #g.\n", z); // expect double
    printf ("<%#G> #G.\n", z); // expect double
    printf ("<%d> is not justified.\n", x);
    printf ("<%d> is not justified.\n", x);
    printf ("<%d> is not justified.\n", x);
    /* Demonstrate with strings. */
    printf ("'%s' is not justified.\n", y);
    printf ("'%10s' is right-justified.\n", y);
    printf ("'%-10s' is left-justified using a minus sign.\n", y);
	/* Complex Structures */
    printf ("<%-#10.5X>\n", x); // minimum 5 digits (first 0x not counted)
    printf ("<%d>\n", x); // minimum 5 digits (first 0x not counted)
    printf ("<%+-7.5d>\n", 42);
    printf ("<%x>\n", 42);
    printf ("<%#1x>\n", 9);
    printf ("<%#1.5x>\n", 9);
    printf("%%d\n");
	
    return 0;
}
