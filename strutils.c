/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:29:06 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 19:12:04 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*move_str_to_chr(const char **format, char c)
{
	const char	*format_start;

	if (*format == NULL)
		return (NULL);
	format_start = *format;
	while (**format)
	{
		(*format)++;
		if (**format == c)
			break ;
	}
	return (ft_substr(format_start, 0, *format - format_start));
}

char	*strjoin_safe(char *s1, char *s2)
{
	char	*res;

	if (s1 && s2 == NULL)
		return (s1);
	else if (s2 && s1 == NULL)
		return (s2);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
