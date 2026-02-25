#include "ft_printf.h"


char	*convert_width(void *str, t_list *lst)
{
	char	*space;
	size_t	val;
	char	*temp_s;
	char 	*s;
	char	c;

	if (get_token_by_val(lst, "0") && get_token_by_val(lst, "0")->type == 'f')
		c = '0';
	else
		c = ' ';
	s = (char *)str;
	temp_s = s;
	val = ft_atoi(get_token_by_type(lst, 'n')->value);
	if (val <= ft_strlen(s))
		return (s);
	val -= ft_strlen(s);
	space = (char *)malloc(sizeof(char) * val + 1);
	ft_memset(space, c, val);
	space[val] = 0;
	if (get_token_by_val(lst, "-"))
		s = ft_strjoin(s, space);
	else
		s = ft_strjoin(space, s);
	free(space);
	free(temp_s);
	return (s);
}

static char *add_hex_prefix(void *content, int capitalize)
{
	char    *s;
	char    *ret;

	s = (char *)content;
	if (*s == '0' && *(s + 1) == '\0') 
		return (s);
	if (capitalize == 0)
		ret = ft_strjoin("0x", s);
	else
		ret = ft_strjoin("0X", s);
	free(s);
	return (ret);
}

char	*convert_d(void *content, t_list *tokens)
{
	int		*np;

	(void)tokens;
	np = (int *)content;
	return (ft_itoa(*np));
}

char    *convert_u(void *content, t_list *tokens)
{
    unsigned int    n;      // Changed to unsigned int
    unsigned int    temp;
    int             len;
    char            *str;
    char            *base = "0123456789"; // Base 10

    (void)tokens;
    // Cast the void pointer to an unsigned int pointer
    n = *(unsigned int *)content; 
    
    temp = n;
    len = (n == 0) ? 1 : 0;
    while (temp != 0)
    {
        temp /= 10;
        len++;
    }
    
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    
    str[len] = '\0';
    if (n == 0)
        str[0] = '0';
        
    while (n != 0)
    {
        str[--len] = base[n % 10];
        n /= 10;
    }
    
    return (str);
}

char	*convert_s(void *content, t_list *tokens)
{
	(void)tokens;
	char **str = content;

	return (ft_strdup(*str));
}

static char *convert_hex(unsigned long n, char *base)
{
    unsigned long    temp;
    int             len;
    char            *str;

    temp = n;
    len = (n == 0) ? 1 : 0;
    while (temp != 0)
    {
        temp /= 16;
        len++;
    }
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    str[len] = '\0';
    if (n == 0)
        str[0] = '0';
    while (n != 0)
    {
        str[--len] = base[n % 16];
        n /= 16;
    }
    return (str);
}

char    *convert_x(void *content, t_list *tokens)
{
    (void)tokens;
    return (convert_hex(*(long *)content, "0123456789abcdef"));
}

char    *convert_bigx(void *content, t_list *tokens)
{
    (void)tokens;
    return (convert_hex(*(long *)content, "0123456789ABCDEF"));
}

char *convert_p(void *content, t_list *tokens)
{
	char *ret;
	void **addr = content;

	ret = convert_x((long *)addr, tokens);
	ret = add_hex_prefix(ret, 0);
	return (ret);
}

char	*hex_small(void *content, t_list *tokens)
{
	long	n;      // Using long to safely handle INT_MIN
	long	temp;
	int		len;
	int		is_neg;
	char	*str;
	char	*base = "0123456789abcdef";

	(void)tokens;
	n = *(int *)content; 
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	temp = n;
	len = (n == 0) ? 1 : 0;
	while (temp != 0)
	{
		temp /= 16;
		len++;
	}
	len += is_neg;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[--len] = base[n % 16];
		n /= 16;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}

char	*convert_plus(void *content, t_list *tokens)
{
	char	*s;
	char	*ret;

	(void)tokens;
	s = (char *)content;
	if (*s == '-')
		return (s);
	if (!get_token_by_val(tokens, "d") && !get_token_by_val(tokens, "i"))
		return (s);
	ret = ft_strjoin("+", s);
	free(s);
	return (ret);
}

char    *convert_space(void *content, t_list *tokens)
{
	char *s;

	if (((char *)content)[0] == '-')
	{
		return ((char *)content);
	}
	if (get_token_by_val(tokens, "d"))
	{
		s = ft_strjoin(" ", (char *)content);
		free(content);
		return (s);
	}
	return ((char *)content);
}

char	*convert_hash(void *content, t_list *tokens)
{
	t_token *token;

	token = get_token_by_type(tokens->next, 's');
	if (token && token->value[0] == 'x')
		{
			return (add_hex_prefix(content, 0));
		}
	if (token && token->value[0] == 'X')
		{
			return (add_hex_prefix(content, 1));
		}
	return ((char *)content);
}



char	*apply_precision(void *content, t_list *tokens)
{
	t_token *specifier_token;
	char	*ret;
	char	*zero_str;
	size_t	prec_len;

	specifier_token = get_token_by_type(tokens->next, 's');
	prec_len = ft_atoi(get_token_by_type(tokens, 'l')->value);
	if (prec_len <= ft_strlen((char *)content))
		return ((char *)content);
	prec_len -= ft_strlen((char *)content);
	if (ft_strncmp(specifier_token->value, "d", 1) == 0 || ft_strncmp(specifier_token->value, "x", 1) == 0)
	{
		zero_str = (char *)malloc(sizeof(char) * prec_len + 1);
		ft_memset(zero_str, 48, prec_len);
		zero_str[prec_len] = 0;
		ret = ft_strjoin(zero_str, (char *)content);
		free(content);
		free(zero_str);
		return (ret);
	}
	return ((char *)content);
}
