/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:55:27 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/13 01:28:57 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	FLAG = 'f',
	WIDTH = 'w',
	PRECISION = '.',
	SPECIFIER = 's',
	DOWNGRADE = '-',
	END = '0'
}	t_token_type;

typedef struct s_token
{
	char	type;
	char	*value;
	int		priority;
	char	*(*f)(void *content, t_list *tokens);
}	t_token;

char	*strjoin_safe(char *s1, char *s2);
char	*move_str_to_chr(const char **format, char c);

int		ft_printf(const char *format, ...);
char	*read_token(const char **format, va_list args, t_token *g_token_buf);

t_token	*get_token_by_type(t_list *lst, const char type);
t_token	*get_token_by_val(t_list *lst, const char *s);
int		is_token(const char c, t_token *tokens, t_token **out);
void	push_token(t_list **lst, t_token *token);
void	int_to_token(const char **format, t_token *out_token);
void	sort_tokens(t_list **tokens);
int		validate_tokens(t_list *lst);

char	*convert_width(void *str, t_list *lst);
char	*convert_c(void *content, t_list *tokens);
char	*convert_d(void *content, t_list *tokens);
char	*convert_u(void *content, t_list *tokens);
char	*convert_s(void *content, t_list *tokens);
char	*convert_x(void *content, t_list *tokens);
char	*convert_p(void *content, t_list *tokens);
char	*convert_bigx(void *content, t_list *tokens);
char	*convert_plus(void *content, t_list *tokens);
char	*convert_hash(void *content, t_list *tokens);
char	*convert_space(void *content, t_list *tokens);
char	*apply_precision(void *content, t_list *tokens);

char	*add_hex_prefix(void *content, int capitalize);

#endif
