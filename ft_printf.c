#include "ft_printf.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
	{
		ft_putstr_fd("free_token: token is null", 2);
		return ;
	}

	if (token->value)
		free(token->value);
	free(token);
}

t_list	*tokenize(const char **format)
{
	t_list	*lst;
	t_token	*token;

	if (**format != '%')
	{
		ft_putstr_fd("tokenize invoked with invalid format", 2);
		return (NULL);
	}

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		ft_putstr_fd("error while malloc token", 2);
		return (NULL);
	}
	token->type = '%';
	token->value = NULL;
	lst = ft_lstnew(token);
	return (lst);
}

void	read_token(const char **format)
{
	t_list	*tokens;

	tokens = tokenize(format);
	(*format)++;
	ft_lstclear(&tokens, free_token);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			read_token(&format);
		}
		ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (1);
} 

int	main(void)
{
	ft_printf("ABC %d", 1);
	return (0);
}
