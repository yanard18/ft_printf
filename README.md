*This project has been created as part of the 42 curriculum by dyanar.*

# Table of Contents

1.  [Description](#org33411dd)
2.  [Instructions](#org07d6895)
    1.  [Compilation](#orgdb73be9)
    2.  [Usage](#orgf43118d)
3.  [Algorithm and Data Structure](#org02e784b)
    1.  [Data Structure](#org234a8ae)
    2.  [Algorithm](#orgca14842)
    3.  [Design Decisions](#org1af2282)
4.  [Variadic Arguments (`va_list`)](#orgd57a85e)
    1.  [Helper Macros](#org84f491e)
5.  [Printf Specification](#orgca6645f)
    1.  [Buffer Implementation](#orgff6432b)
    2.  [Project Structure and Rules](#org52ae599)
    3.  [Implementation Notes](#orga7515fb)
6.  [GDB Tips](#org8c983e0)
    1.  [Coredumping](#orgb5614ad)
    2.  [GDB Printing List](#orgff0ab4a)
7.  [Tester](#orgfc22429)
8.  [Resources](#org85f339b)
    1.  [Classic References](#orgb115d2e)
    2.  [AI Usage](#org3444916)



<a id="org33411dd"></a>

# Description

This project is a custom implementation of the standard C library function `printf`. The primary goal is to learn how to efficiently manage variadic arguments in C, handle complex string parsing, and deepen understanding of standard output writing without relying on the internal buffering of the original `printf`.

It handles standard conversion specifiers (such as `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%%`) and generates a static library (`libftprintf.a`) that will serve as a core utility function for future projects in the 42 curriculum.


<a id="org07d6895"></a>

# Instructions


<a id="orgdb73be9"></a>

## Compilation

To compile the library, run the provided Makefile at the root of the repository. It will automatically compile the required `libft` dependencies and build the main project.

    make

This will generate the `libftprintf.a` static library.


<a id="orgf43118d"></a>

## Usage

To use the function in your code, include the header in your C files:

    #include "ft_printf.h"

Then, compile your project by linking the compiled static library:

    cc your_main.c -L. -lftprintf -o your_program


<a id="org02e784b"></a>

# Algorithm and Data Structure


<a id="org234a8ae"></a>

## Data Structure

The project utilizes a Linked List data structure (represented by `t_token` nodes) to manage parsed segments of the format string. Each node in the list represents either a standard string literal or a specific conversion specifier that needs to be formatted and printed.

-   **Justification:** A linked list allows for dynamic and flexible parsing of the format string without needing to know the total number of arguments or the final string length in advance. It avoids the rigidity of static arrays and allows the program to scale with complex format strings.


<a id="orgca14842"></a>

## Algorithm

The core algorithm relies on a **Tokenizer**. The format string is read sequentially. When a `%` character is encountered, the tokenizer isolates the subsequent characters to identify the conversion specifier, while standard text is grouped as separate tokens.

-   **Justification:** As noted in the design decisions, tokenization provides a modular approach to parsing. Instead of managing complex state machines within a single monolithic loop, breaking the string down into discrete tokens allows each conversion type to be handled by isolated, specialized helper functions (e.g., `convert_s`). While the current implementation allocates memory sequentially, this tokenized structure paves the way for future optimizations (like assembling the entire string sequence before issuing a single `write` call).


<a id="org1af2282"></a>

## Design Decisions

Decided to only tokenize the conversion specifiers and print the strings without allocating memory. However I realized that original printf, prints an empty string if contains any invalid conversion specifier.

To fix this, decided to allocate strings with strjoin and allocate the conversion specifiers with tokenization. However better approach would be tokenize the whole text then print the whole token chain at once. This can be a future development task.

This would also fix the issue that, current system initialize a token<sub>buf</sub> each time for read<sub>token</sub>(). Here, bad design implemented because I was not aware that static globals are forbiden for this project. To be honest I still believe that making token<sub>buf</sub> global is best approach for both memory and extendibility.


<a id="orgd57a85e"></a>

# Variadic Arguments (`va_list`)

The `va_list` type is used to retrieve additional arguments in a function. On many systems (like x86<sub>64</sub>), it is implemented as a structure:

    $1 = {{gp_offset = 2, fp_offset = 0, overflow_arg_area = 0xbfebfbff,
    		reg_save_area = 0x7fffffffe6b9}}

-   **gp<sub>offset</sub>**: Offset to the next available general-purpose register in the `reg_save_area`.
-   **fp<sub>offset</sub>**: Offset to the next available floating-point register in the `reg_save_area`.
-   **reg<sub>save</sub><sub>area</sub>**: Pointer to the memory area where registers are saved.
-   **overflow<sub>arg</sub><sub>area</sub>**: Pointer to the area where arguments passed on the stack are stored.

*Note: The implementation of va<sub>list</sub> is platform-dependent and may not be a struct on all systems.*


<a id="org84f491e"></a>

## Helper Macros

-   `va_start`: Initializes the `va_list` object to retrieve the additional arguments.
-   `va_arg`: Retrieves the value of the next argument in the list and advances the pointer.
-   `va_end`: Cleans up the `va_list` object.


<a id="orgca6645f"></a>

# Printf Specification

Each conversion specification begins with the `%` character and ends with a conversion specifier.

**Full Format Pattern**:
`% [flags] [field_width] [.precision] [length] [conversion_specifier]`


<a id="orgff6432b"></a>

## Buffer Implementation

The standard `printf` is buffered, meaning it stores data in an internal buffer and displays it on the screen in a single call via `fflush(stdout)` or when the buffer is full.

**Constraint**: This implementation will not include a buffer.


<a id="org52ae599"></a>

## Project Structure and Rules

**Requirements**

-   All `libft` associated files must be located within the `libft/` folder.
-   A **Recursive Makefile** should be used to manage dependencies between the main project and `libft`.


<a id="orga7515fb"></a>

## Implementation Notes

-   **Tokenization**: For logic regarding parsing the format string, refer to the principles of tokenization (e.g., *Programming Principles and Practice using C++*, Chapter 5).
-   **Security**: Be aware of **Format String Attacks**, where a user-controlled string is passed as the format argument.


<a id="org8c983e0"></a>

# GDB Tips


<a id="orgb5614ad"></a>

## Coredumping

How to create core dump file:

    ulimit -c unlimited
    ./a.out 
    gdb ./a.out core

Then to debug

1.  Use backtrace (`br`) command. It will map how the program crahsed.

      (gdb) bt
    #0  0x00005585075b77de in ft_strlen ()
    #1  0x00005585075b7488 in ft_strdup ()
    #2  0x00005585075b6a21 in convert_s (content=0x7ffdcc9a6610, tokens=0x55853467c2d0) at token_helper.c:101
    #3  0x00005585075b64a6 in apply_specifier (lst=0x55853467c2d0, args=0x7ffdcc9a6698) at token.c:164
    #4  0x00005585075b6678 in read_token (format=0x7ffdcc9a6688, args=0x7ffdcc9a6698) at token.c:236
    #5  0x00005585075b5ef4 in ft_printf (format=0x5585075b851b "") at ft_printf.c:17
    #6  0x00005585075b39aa in main ()

1.  Use frame (`frame 2`) command. It will map how the program crahsed.

    (gdb) frame 2
    #2  0x00005585075b6a21 in convert_s (content=0x7ffdcc9a6610, tokens=0x55853467c2d0) at token_helper.c:101
    101		return (ft_strdup(*str));

1.  Use (`list`) to display surrounding code in the frame.
2.  displayer args (`infor args`).
3.  displayer local variables (`info locals`).

Then revert core dump creation back to normal (0).

    ulimit -c 0


<a id="orgff0ab4a"></a>

## GDB Printing List

Manual while iteration in gdb:

    set $node = lst
    while $node != 0
      print $node->content
      set $node = $node->next
    end

lst represent the HEAD node of the list.

Same idea also possible with user-defined function writing inside the `~/.gdbinit` file (or type in the session).

    define plist
      set $curr = $arg0
      while $curr != 0
    	set $t = $curr->content
    	set $t = (t_token *)$t
    	p *$t
    	set $curr = $curr->next
      end
    end
    
    document plist
      Print a linked list. Syntax: plist <head_pointer>
    end


<a id="orgfc22429"></a>

# Tester

Main design idea of this tester to have minimum amount of duplication while testing variadic functions and comapring two identical functions.

1.  Only have TEST<sub>STDOUT</sub><sub>FUNC</sub> func (macro func)
2.  Directly compare two functions
3.  No duplication while passing arguments
4.  Supports multiple files and registering more tests
5.  TEST<sub>STDOUT</sub><sub>FUNC</sub> test both stdout and return values


<a id="org85f339b"></a>

# Resources


<a id="orgb115d2e"></a>

## Classic References

-   [C Functions - Format](https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html)
    -   Makefile
        -   [Make file recursion](https://www.gnu.org/software/make/manual/html_node/Recursion.html)
        -   [ar script](https://sourceware.org/binutils/docs-2.29/binutils/ar-scripts.html)
        -   [.ONESHELL](https://www.gnu.org/software/make/manual/make.html#One-Shell)
        -   [Makefile for tester](https://github.com/Tripouille/libftTester/blob/master/Makefile)
    -   Tokenization
        -   *Programming Principles and Practice with C++*, Chapter 5


<a id="org3444916"></a>

## AI Usage

-   **Task:** README structuring and requirement validation.
-   **Tool:** Google Gemini.
-   **Usage:** AI was used to draft the mandatory 42 curriculum sections (Description, Instructions, Algorithm/Data Structure) and ensure formatting compliance with project requirements. No AI was used to generate the core logic or C code of `ft_printf`.

