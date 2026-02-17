#include "ft_printf.h"

char	*itoa(void *content, t_list *tokens)
{
	int		*np;

	(void)tokens;
	np = (int *)content;
	return (ft_itoa(*np));
}

char	*get_str(void *content, t_list *tokens)
{
	(void)tokens;
	char **str = content;

	return (ft_strdup(*str));
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

char	*apply_plus_flag(void *content, t_list *tokens)
{
	char	*s;
	char	*ret;

	(void)tokens;
	s = (char *)content;
	if (*s == '-')
		return (s);
	ret = ft_strjoin("+", s);
	free(s);
	return (ret);
}

char	*apply_hash_token(void *content, t_list *tokens)
{
	char	*s;
	t_token *token;

	s = (char *)content;
	token = get_token(tokens->next, 's');
	if (ft_strncmp(token->value, "x", 1) == 0)
		content = ft_strjoin("0x", (char *)content);
	else if (ft_strncmp(token->value, "X", 1) == 0)
		content = ft_strjoin("0X", (char *)content);
	free(s);
	return ((char *)content);
}

char	*apply_precision(void *content, t_list *tokens)
{
	t_token *specifier_token;
	char	*ret;
	char	*zero_str;
	size_t	prec_len;

	specifier_token = get_token(tokens->next, 's');
	prec_len = ft_atoi(get_token(tokens, 'l')->value);
	if (prec_len <= ft_strlen((char *)content))
		return ((char *)content);
	prec_len -= ft_strlen((char *)content);
	if (ft_strncmp(specifier_token->value, "d", 1) == 0)
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
