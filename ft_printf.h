/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2026/02/12 04:45:32 by dyanar            #+#    #+#             */
/*   Updated: 2026/02/17 17:53:18 by dyanar           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

typedef	struct	s_token {
	char	type;
	char	*value;
	char	*(*f)(void *content, t_list *tokens);
}				t_token;

int		ft_printf(const char *format, ...);
void	read_token(const char **format, va_list args);
t_token	*get_token(t_list* lst, const char type);

void	debug_token(void *content);
void	debug_tokenlst(t_list *tokens);

char	*itoa(void *content, t_list *tokens);
char	*get_str(void *content, t_list *tokens);
char	*hex_small(void *content, t_list *tokens);
char	*apply_plus_flag(void *content, t_list *tokens);
char	*apply_hash_token(void *content, t_list *tokens);

#endif
