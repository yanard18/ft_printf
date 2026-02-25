#ifndef PRINTF_TESTER_H
# define PRINTF_TESTER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

# define BUFFER_SIZE	1024
/* Standard ANSI Colors */
#define RED     "\033[31m"
#define GREEN   "\033[0m"
#define RESET   "\033[0m"

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
		dprintf(saved_stdout, GREEN "[+] Succeed: %s, expected: \"%s\"\n" RESET, #print, exp);\
	else\
		dprintf(saved_stdout, RED "[-] Fail: %s, expected: \"%s\", was: \"%s\"\n\033[0m" RESET, #print, exp, buf);\
}

# define TEST_RETURN(exp, print) {\
	ret = print;\
	printf("%c", '\0');\
	fflush(stdout);\
	memset(buf, 0, 1024);\
	read(fd[0], buf, sizeof(buf) - 1);\
	if (ret == exp)\
		dprintf(saved_stdout, GREEN "[+] Succeed: RETURN: %s, expected: %d\n" RESET, #print, exp);\
	else\
		dprintf(saved_stdout, RED "[-] Fail: RETURN: %s, expected: %d, was: %d\n" RESET, #print, exp, ret);\
	ret = 0;\
}

# define TEST_STDOUT_FUNC(exp_f, res_f) {\
	exp_f;\
	printf("%c", '\0');\
	fflush(stdout);\
	memset(buf, 0, 1024);\
	read(fd[0], buf, sizeof(buf) - 1);\
	res_f;\
	printf("%c", '\0');\
	fflush(stdout);\
	memset(buf2, 0, 1024);\
	read(fd[0], buf2, sizeof(buf2) - 1);\
if (strcmp(buf, buf2) == 0)\
		dprintf(saved_stdout, GREEN "[+] Succeed: %s, expected: \"%s\"\n" RESET, #res_f, buf);\
	else\
		dprintf(saved_stdout, RED "[-] Fail: %s, expected: \"%s\", was: \"%s\"\n" RESET, #res_f, buf, buf2);\
}

char	buf[BUFFER_SIZE];
char	buf2[BUFFER_SIZE];
int		fd[2];
int		saved_stdout;
int		ret = 0;

#endif
