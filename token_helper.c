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
	return (ft_strdup((char *)content));
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
	char	*token_val;
	t_token *token;

	s = (char *)content;
	token = get_token(tokens->next, 's');
	token_val = (char *)token->value;
	if (ft_strncmp(token_val, "x", 1) == 0)
		s = ft_strjoin("0x", s);
	if (ft_strncmp(token_val, "X", 1) == 0)
		s = ft_strjoin("0X", s);
	return (s);

}
