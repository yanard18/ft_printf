/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2026/02/12 04:45:32 by dyanar            #+#    #+#             */
/*   Updated: 2026/02/18 05:31:10 by dyanar           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

typedef	struct	s_token {
	char	type;
	char	*value;
	int		priority;
	char	*(*f)(void *content, t_list *tokens);
}				t_token;

int			ft_printf(const char *format, ...);
ssize_t		read_token(const char **format, va_list args, t_token *g_token_buf);
t_token		*get_token_by_type(t_list* lst, const char type);
t_token		*get_token_by_val(t_list *lst, const char *s);

void	debug_token(void *content);
void	debug_tokenlst(t_list *tokens);

char	*convert_width(void *str, t_list *lst);
char	*convert_d(void *content, t_list *tokens);
char    *convert_u(void *content, t_list *tokens);
char	*convert_s(void *content, t_list *tokens);
char    *convert_x(void *content, t_list *tokens);
char    *convert_p(void *content, t_list *tokens);
char    *convert_bigx(void *content, t_list *tokens);
char	*convert_plus(void *content, t_list *tokens);
char	*convert_hash(void *content, t_list *tokens);
char	*convert_space(void *content, t_list *tokens);
char	*apply_precision(void *content, t_list *tokens);

#endif
