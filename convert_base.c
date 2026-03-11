/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:08:59 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/12 01:09:01 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *convert_base_generic(unsigned long n, char *base, unsigned long base_len)
{
    unsigned long   temp;
    int             len;
    char            *str;

    temp = n;
    len = (n == 0);
    while (temp != 0)
    {
        temp /= base_len;
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
        str[--len] = base[n % base_len];
        n /= base_len;
    }
    return (str);
}

char	*convert_u(void *content, t_list *tokens)
{
	(void)tokens;
	return (convert_base_generic(*(unsigned int *)content, "0123456789", 10));
}

char	*convert_x(void *content, t_list *tokens)
{
	(void)tokens;
	return (convert_base_generic(*(unsigned int *)content, "0123456789abcdef", 16));
}

char	*convert_bigx(void *content, t_list *tokens)
{
	(void)tokens;
	return (convert_base_generic(*(unsigned int *)content, "0123456789ABCDEF", 16));
}

char	*convert_p(void *content, t_list *tokens)
{
	char	*ret;
	void	**addr;

	addr = content;
	if (*addr == 0)
		return (ft_strdup("(nil)"));
	ret = convert_x((long *)addr, tokens);
	ret = add_hex_prefix(ret, 0);
	return (ret);
}
