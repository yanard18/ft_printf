/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanar <dyanar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:18:28 by dyanar            #+#    #+#             */
/*   Updated: 2026/03/11 20:20:39 by dyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	validate_tokens(t_list *lst)
{
	if (!lst)
		return (0);
	if (get_token_by_type(lst, SPECIFIER) == NULL)
		return (0);
	return (1);
}
