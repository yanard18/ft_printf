#ifndef PRINTF_TESTER_H
# define PRINTF_TESTER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

# define BUFFER_SIZE	1024

# define INIT {\
	saved_stdout = dup(1);\
	pipe(fd);\
	dup2(fd[1], 1);\
}

# define TEARDOWN {\
	dup2(saved_stdout, 1);\
	close(fd[1]);\
	close(fd[0]);\
}

# define TEST(exp, print) {\
	print;\
	printf("%c", '\0');\
	fflush(stdout);\
	memset(buf, 0, 1024);\
	read(fd[0], buf, sizeof(buf) - 1);\
	if (strcmp(exp, buf) == 0)\
		dprintf(saved_stdout, "[+] Succeed: %s\n", #print);\
	else\
		dprintf(saved_stdout, "[-] Fail: %s, expected: %s, was: %s\n", #print, exp, buf);\
}

char	buf[BUFFER_SIZE];
int		fd[2];
int		saved_stdout;

#endif
