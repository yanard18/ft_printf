/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2026/02/12 04:45:32 by dyanar            #+#    #+#             */
/*   Updated: 2026/02/16 20:06:27 by dyanar           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

typedef	struct	s_token {
	char	type;
	void	*value;
	char	*(*f)(void *content);
}				t_token;

int		ft_printf(const char *format, ...);
void	read_token(const char **format, va_list args);

void	debug_token(void *content);
void	debug_tokenlst(t_list *tokens);

char	*itoa(void *content);
char	*get_str(void *content);
char	*hex_small(void *content);
char	*apply_plus_flag(void *content);

#endif
