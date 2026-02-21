/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_lstiter.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:51 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:51 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
