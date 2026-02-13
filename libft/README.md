*This project has been created as part of the 42 curriculum by dyanar*

## Description

libft, is the re-implementation of the standard c library as the 42 school's first project. Goal of the project is understanding memory, handlings leaks and understainding selected libc functions to eexpand on further 42projects.

README.md page shows instructions, resources and information that I evaluate as valuable. I do not write explaining the functions since such information could be find any other 42libft repo, instead I prioritize caviats.
### Functions Included
- ft_isalpha 
- ft_isdigit 
- ft_isalnum 
- ft_isascii 
- ft_isprint 
- ft_strlen 
- ft_memset
- ft_bzero
- ft_memcpy
- ft_memmove
- ft_strlcpy
- ft_strlcat
- ft_toupper
- ft_tolower
- ft_strchr
- ft_strrchr
- ft_strncmp
- ft_memchr
- ft_memcmp
- ft_strnstr
- ft_atoi
- ft_calloc
- ft_strdup
- ft_substr
- ft_strjoin
- ft_strtrim
- ft_split
- ft_itoa
- ft_strmapi
- ft_striteri
- ft_putchar_fd
- ft_putstr_fd
- ft_putendl_fd
- ft_putnbr_fd
- ft_lstnew
- ft_lstadd_front
- ft_lstsize
- ft_lstlast
- ft_lstadd_back
- ft_lstdelone
- ft_lstclear
- ft_lstiter
- ft_lstmap

## Instructions
`make` to compile mendatory functions.

`make run` to compile and execute (only work if one main() function exist)

## Memory Dumping

`ft_mem\*` functions requires good understanding of memory. I found gdb tool to be the most useful while examine memory.

```c
int	main(void)
{
	int	x;

	x = 0;
	ft_memset(&x, 0xA1B2C3D4, 8);
	return (0);
}


```

```gdb
Breakpoint 1, main () at ft_memset.c:32
(gdb) n
(gdb) n
(gdb) print &x
$1 = (int *) 0x7fffffffe228
(gdb) x /16xb $1
0x7fffffffe228: 0xd4    0xd4    0xd4    0xd4    0xd4    0xd4    0xd4    0xd4
0x7fffffffe230: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
```

with `x /16xb $1` tool we dump the memory of `&x`, see that `ft_memset` operation wrote 0xD4 byte 8 times. This is the expected behaviour since memset operation only read the first byte at the provided value's address. But why not 0xA1? Answer came from Little Endian rule.

> big-endian system stores the most significant byte of a word at the smallest memory address and the least significant byte at the largest.

What we understand by this statement; `int` variables stored in memory in reverse order. This fit our situation since memset accepts an `int` as its second variable, and we provided exactly 4 bytes value (`0xA1B2C3D4`).

![image](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/32bit-Endianess.svg/1280px-32bit-Endianess.svg.png)

## Libraries

https://en.wikipedia.org/wiki/C_standard_library

libc.a located at:

```bash
$ find /usr/lib -name "libc.*" 2>/dev/null
/usr/lib/x86_64-linux-gnu/libc.so.6
/usr/lib/x86_64-linux-gnu/libc.so
/usr/lib/x86_64-linux-gnu/libc.a
```
.a files are static libraries, .so means shared object and is the Linux equivalent of a DLL.

> A static library(.a) is a library that can be linked directly into the final executable produced by the linker; it is contained in it and there is no need to have the library in the system where the executable will be deployed.

> A shared library(.so) is a library that is linked but not embedded in the final executable, so it will be loaded when the executable is launched and needs to be present in the system where the executable is deployed.

Reference: https://stackoverflow.com/questions/9688200/difference-between-shared-objects-so-static-libraries-a-and-dlls-so

Checking which shared libraries linked to our `libft`

```bash
$ ldd a.out
	linux-vdso.so.1 (0x00007fb0bb2ea000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fb0bb000000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fb0bb2ec000)
```

## Testing Methadology

42schools are very strict with their edge case handling, which also required practice for safe C code. Often mulinette blow us with some weird parameters. So I decided to improve my ability on writing tests. Created a simple workflow for each c code.

1. Static Analysis
2. Memory Leaks
3. Stress Testing
4. Structurall Testing
5. (OPTIONAL)Additional Tests

### 1. Static Analysis

Main idea to just be sure code compiled correctly.

```bash
cc -Wall Wextra Werror main.c
```

### 2. Memory Leaks

- `fsanitize=address`
- Valgrind

implementing a use-after-free leak for purpose

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	char *s = malloc(100);
	free(s);
	strcpy(s, "Hello world!");
	printf("string is: %s\n", s);
	return 0;
}
```
compile

```bash
cc main.c -fsanitize=address
```

```out
==1234668==ERROR: AddressSanitizer: heap-use-after-free on address 0x60b0000000f0 at pc 0x000000485b98 bp 0x7fff67f19a20 sp 0x7fff67f191e0
WRITE of size 13 at 0x60b0000000f0 thread T0
#0 0x485b97 in strcpy (/home/dyanar/Documents/git/libft/a.out+0x485b97)
#1 0x4cb1fa in main (/home/dyanar/Documents/git/libft/a.out+0x4cb1fa)
#2 0x7f9070429d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
#3 0x7f9070429e3f in __libc_start_main csu/../csu/libc-start.c:392:3
#4 0x41f2a4 in _start (/home/dyanar/Documents/git/libft/a.out+0x41f2a4)

0x60b0000000f0 is located 0 bytes inside of 100-byte region [0x60b0000000f0,0x60b000000154)
freed by thread T0 here:
#0 0x499f02 in free (/home/dyanar/Documents/git/libft/a.out+0x499f02)
#1 0x4cb1ec in main (/home/dyanar/Documents/git/libft/a.out+0x4cb1ec)
#2 0x7f9070429d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

previously allocated by thread T0 here:
#0 0x49a16d in malloc (/home/dyanar/Documents/git/libft/a.out+0x49a16d)
#1 0x4cb1df in main (/home/dyanar/Documents/git/libft/a.out+0x4cb1df)
#2 0x7f9070429d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-use-after-free (/home/dyanar/Documents/git/libft/a.out+0x485b97) in strcpy
Shadow bytes around the buggy address:
0x0c167fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x0c167fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x0c167fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x0c167fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0x0c167fff8000: fa fa fa fa fa fa fa fa fd fd fd fd fd fd fd fd
=>0x0c167fff8010: fd fd fd fd fd fa fa fa fa fa fa fa fa fa[fd]fd
0x0c167fff8020: fd fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa
0x0c167fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
0x0c167fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
0x0c167fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
0x0c167fff8060: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
	Addressable:           00
	Partially addressable: 01 02 03 04 05 06 07
	Heap left redzone:       fa
	Freed heap region:       fd
	Stack left redzone:      f1
	Stack mid redzone:       f2
	Stack right redzone:     f3
	Stack after return:      f5
	Stack use after scope:   f8
	Global redzone:          f9
	Global init order:       f6
	Poisoned by user:        f7
	Container overflow:      fc
	Array cookie:            ac
	Intra object redzone:    bb
	ASan internal:           fe
	Left alloca redzone:     ca
	Right alloca redzone:    cb
	Shadow gap:              cc
	==1234668==ABORTING
```

Shadow Memory Dump from AddressSanitizer (ASan) maps every **8-bytes** of the program's actual memory to 1 shadow byte. One `00` means 8 valid bytes.
`0x0c167fff8010` is the shadow address.

line exactly show where the program tried to access the memory

```bash
=>0x0c167fff8010: fd fd fd fd fd fa fa fa fa fa fa fa fa fa[fd]fd
```

- `fa` is 'Heap Redzone' that catches heap out-of-bounds errors.
- `fd` is 'Freed Area' in our case, we try to access freed area.
- `00` valid memory, any access is legal.


Another example, heap-buffer-overflow

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	char *s = malloc(12);
	strcpy(s, "Hello world!");
	printf("string is: %s\n", s);
	free(s);
	return 0;
}
```

ASan output:

```bash
=>0x0c047fff8000: fa fa 00[04]fa fa fa fa fa fa fa fa fa fa fa fa
```

- `00` byte represent 8 valid bytes
- `04` means partially available 04 bytes (since we malloced 12 bytes)

Valgrind also useful to check memory leaks. Comparing to FSan, Valgrind do now use shadow bytes and display exact addressess which might be more useful and note that it's more than a memory analysis tool.

Hit on [04] because "Hello World!" attempted to write 13 bytes.

### 3. Stress Testing

### 4. Structural Testing

### 5. (OPTIONAL) Additional Tests

## Resources
- Useful repos to compare libft functions with standard c library libc
	- https://github.com/freebsd/freebsd-src/tree/main
	- https://github.com/bminor/glibc
	- check `/usr/lib/
- Excellent resource to learn Makefile
	- https://makefiletutorial.com/
- GDB manual by GNU
	- https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_toc.html
- Endianness
	- https://en.wikipedia.org/wiki/Endianness
- FSan
	- https://www.osc.edu/resources/getting_started/howto/howto_use_address_sanitizer
- Valgrind
	- https://valgrind.org/docs/manual/index.html

3. Structural Testing


## Further Study

### LDD

> some versions of ldd may attempt to obtain the dependency information by attempting to directly  execute  the program,  which may lead to the execution of whatever code is defined in the program's ELF interpreter, and perhaps to execution of the program itself.

Can be interesting.
