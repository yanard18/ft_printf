### Variadic Arguments (`va_list`)
The va_list type is used to retrieve additional arguments in a function. On many systems (like x86_64), it is implemented as a structure:

```gdb
$1 = {{gp_offset = 2, fp_offset = 0, overflow_arg_area = 0xbfebfbff,
	    reg_save_area = 0x7fffffffe6b9}}
```
- gp_offset: Offset to the next available general-purpose register in the reg_save_area.
- fp_offset: Offset to the next available floating-point register in the reg_save_area.
- reg_save_area: Pointer to the memory area where registers are saved.
- overflow_arg_area: Pointer to the area where arguments passed on the stack are stored.
Note: The implementation of va_list is platform-dependent and may not be a struct on all systems.
Helper Macros
- va_start: Initializes the va_list object to retrieve the additional arguments.
- va_arg: Retrieves the value of the next argument in the list and advances the pointer.
- va_end: Cleans up the va_list object.

---

## Printf Specification

Each conversion specification begins with the % character and ends with a conversion specifier.

*Full Format Pattern*:
% [flags] [field_width] [.precision] [length] [conversion_specifier]
Buffer Implementation

The standard printf is buffered, meaning it stores data in an internal buffer and displays it on the screen in a single call via fflush(stdout) or when the buffer is full.

Constraint: This implementation will not include a buffer.

---

## Project Structure and Rules
*Requirements*
- All libft associated files must be located within the libft/ folder.
- A Recursive Makefile should be used to manage dependencies between the main project and libft.

*Implementation Notes*

    Tokenization: For logic regarding parsing the format string, refer to the principles of tokenization (e.g., Programming Principles and Practice using C++, Chapter 5).

    Security: Be aware of Format String Attacks, where a user-controlled string is passed as the format argument.
### Format String Attacks
- liveoverflow has video

## References
- https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html
- Makefile
	- [make file recursion](https://www.gnu.org/software/make/manual/html_node/Recursion.html)
	- [ar script](https://sourceware.org/binutils/docs-2.29/binutils/ar-scripts.html)
	- [.ONESHELL](https://www.gnu.org/software/make/manual/make.html#One-Shell)
	- [makefile for tester](https://github.com/Tripouille/libftTester/blob/master/Makefile)
- Tokenization
	- programming principles and practice with c++, chapter 5
