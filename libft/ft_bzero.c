/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_bzero.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:52 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:52 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*(ptr + i) = 0;
		i++;
	}
}
