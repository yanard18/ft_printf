#include "ft_printf.h"

static void lstpush_token(t_list **lst, char type, void *value)
{
	t_list	*newlst;
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	newlst = ft_lstnew(token);
	ft_lstadd_back(lst, newlst);
}

static t_list	*tokenize(const char *format)
{
	t_list	*lst; 

	if (*format != '%')
	{
		ft_putstr_fd("invalid 'format' given to tokenize()", 2);
		return (NULL);
	}

	lst	= ft_lstnew(&(t_token){'%', NULL});

	format++;
	while (*format)
	{
		if (ft_isdigit(*format))
		{
			lstpush_token(&lst, '9', &(int){ft_atoi(format)});
			while (ft_isdigit(*format))
				format++;
		}
		else if (*format == 'd')
		{
			lstpush_token(&lst, 'C', "d");
			format++;
		}
		else
			format++;
	}
	ft_lstiter(lst, debug_lst);
	return (lst);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		ft_putchar_fd(*format, 1);
		if (*format == '%')
			tokenize(format);
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
