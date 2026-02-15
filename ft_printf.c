#include "libft/libft.h"
#include "ft_printf.h"

static void debug_lst(void *content)
{
	return ;
	t_token	*token;
	int	fd;

	fd = 2;
	token = (t_token *)content;
	ft_putchar_fd(token->type, fd);
	ft_putstr_fd("->", 1);
	if (token->value == NULL)
		ft_putstr_fd("NULL", fd);
	else if (token->type == '9')
		ft_putstr_fd(ft_itoa(*((int *)token->value)), fd);
	else
		ft_putstr_fd((char *)token->value, fd);
	ft_putchar_fd('\n', fd);
}
static t_list	*tokenize(const char *format)
{
	t_list	*lst; 
	t_list	*newlst;
	int		nbr;

	if (*format != '%')
	{
		ft_putstr_fd("invalid 'format' given to tokenize()", 2);
		return (NULL);
	}

	lst	= ft_lstnew(&(t_token){'%', NULL});

	while (*format)
	{
		if (ft_isdigit(*format))
		{
			// tokenize
			nbr = ft_atoi(format);
			newlst = ft_lstnew(&(t_token){'9', &nbr});
			ft_lstadd_back(&lst, newlst);
			while (ft_isdigit(*format))
				format++;
		}
		else if (*format == 'd')
		{
			newlst = ft_lstnew(&(t_token){'C', "d"});
			ft_lstadd_back(&lst, newlst);
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


	va_start(args, format); // init
	while (*format)
	{
		ft_putchar_fd(*format, 1);
		if (*format == '%')
			tokenize(format);
		format++;
	}

	
	va_end(args); // free
	return (1);
} 

/*
int	main(void)
{
	ft_printf("ABC %d", 1);
	return (0);
}
*/
