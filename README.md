### VA_LIST Struct
$1 = {{gp_offset = 2, fp_offset = 0, overflow_arg_area = 0xbfebfbff,
	    reg_save_area = 0x7fffffffe6b9}}

- It may not be struct on some systems

gp_offset = offset pointer that points the current list
reg_save_area = the area that each value from variadiac variable will be stored

### VA_LIST Helper Methods
va_start: initialize the linked list
va_arg: get value of the current node then step onto next node
va_end: free the linked list

### printf Description
Each conversion specification is introduced by the charac‐
       ter %, and ends with a conversion specifier.

### printf buffer implementation
original printf do not print immediately, instead it save data on buffer then display on screen on one call via `fflush(stdout)`

### printf flag format

% (flags) (field_width) (precision) (length) (conversion specifier)


% \[zero or more flag\] \[optional field width\] \[optional precision\] \[length\] \[conversion specifier\]



### Format String Attacks
- liveoverflow has video

## Recursive Makefile

## Notes

- Do not implement printf buffer
- libft associated files should be located in `libft/` folder

## Tester
- https://gcc.gnu.org/onlinedocs/cpp/Macros.html

## References
- https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html
- Makefile
	- [make file recursion](https://www.gnu.org/software/make/manual/html_node/Recursion.html)
	- [ar script](https://sourceware.org/binutils/docs-2.29/binutils/ar-scripts.html)
	- [.ONESHELL](https://www.gnu.org/software/make/manual/make.html#One-Shell)
	- [makefile for tester](https://github.com/Tripouille/libftTester/blob/master/Makefile)
- Tokenization
	- programming principles and practice with c++, chapter 5
