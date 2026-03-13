#ifndef PRINTF_TESTER_H
# define PRINTF_TESTER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* Standard ANSI Colors */
#define RED     "\033[31m"
#define GREEN   "\033[0m"
#define RESET   "\033[0m"

typedef struct s_test {
	const char *name;
	void (*func)(void);
	struct s_test *next;
} t_test;

extern t_test *g_test_lst;

void register_test(const char *name, void (*func)(void));

# define REGISTER_TEST(func_ptr)				\
	__attribute__((constructor))				\
	static void register_##func_ptr(void) {		\
		register_test(#func_ptr, func_ptr);		\
		printf("register: %s\n", #func_ptr);	\
	}											

# define BUFFER_SIZE	1024
# define TEST_STDOUT_FUNC(exp_f, res_f, ...) {							\
		{																\
			char	buf[BUFFER_SIZE];									\
			char	buf2[BUFFER_SIZE];									\
			int		fd[2];												\
			int		saved_stdout;										\
			fflush(stdout);												\
			saved_stdout = dup(1);										\
			pipe(fd);													\
			dup2(fd[1], 1);												\
			int exp_ret;												\
			int res_ret;												\
			exp_ret = exp_f(__VA_ARGS__);								\
			printf("%c", '\0');											\
			fflush(stdout);												\
			memset(buf, 0, 1024);										\
			read(fd[0], buf, sizeof(buf) - 1);							\
			res_ret = res_f(__VA_ARGS__);								\
			printf("%c", '\0');											\
			fflush(stdout);												\
			memset(buf2, 0, 1024);										\
			read(fd[0], buf2, sizeof(buf2) - 1);						\
			if (strcmp(buf, buf2) == 0 && exp_ret == res_ret)			\
				dprintf(saved_stdout, GREEN "[+] Succeed: for %s(%s) --> stdout: \"%s\" ret: %i\n" RESET, #res_f, #__VA_ARGS__, buf, exp_ret); \
			else														\
				dprintf(saved_stdout, RED "[-] Fail: %s(%s) --> expected stdout: \"%s\", was: \"%s\" expected ret: %i was: %i\n" RESET, #res_f, #__VA_ARGS__, buf, buf2, exp_ret, res_ret); \
			dup2(saved_stdout, 1);										\
			close(fd[1]);												\
			close(fd[0]);												\
		}																\
	}


#endif
