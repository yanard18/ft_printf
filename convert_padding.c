#include "ft_printf.h"

char    *convert_width(void *str, t_list *lst)
{
    char    *space;
    size_t    val;
    char    c;

    c = ' ';
    if (get_token_by_val(lst, "-") && get_token_by_val(lst, "-")->type == FLAG)
        c = ' ';
    else if (get_token_by_val(lst, "0") && get_token_by_val(lst, "0")->type == FLAG)
        c = '0';
    val = ft_atoi(get_token_by_type(lst, 'w')->value);
    if (val <= ft_strlen((char *)str))
        return ((char *)str);
    val -= ft_strlen((char *)str);
    space = (char *)malloc(sizeof(char) * val + 1);
    ft_memset(space, c, val);
    space[val] = 0;
    if (get_token_by_val(lst, "-"))
        str = (char *)strjoin_safe((char *)str, space);
    else
        str = (char *)strjoin_safe(space, (char *)str);
    return ((char *)str);
} 

char	*apply_precision(void *content, t_list *tokens)

{
	t_token	*spec;
	char	*ret;
	char	*zero_str;
	size_t	prec;

	spec = get_token_by_type(tokens->next, 's');
	prec = ft_atoi(get_token_by_type(tokens, '.')->value);
	if (prec <= ft_strlen((char *)content))
		return ((char *)content);
	prec -= ft_strlen((char *)content);
	if (spec && (spec->value[0] == 'd' || spec->value[0] == 'x'))
	{
		zero_str = (char *)malloc(prec + 1);
		ft_memset(zero_str, '0', prec);
		zero_str[prec] = '\0';
		ret = ft_strjoin(zero_str, (char *)content);
		free(content);
		free(zero_str);
		return (ret);
	}
	return ((char *)content);
}
