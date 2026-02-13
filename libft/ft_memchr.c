/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_memchr.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/27 04:04:16 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/03 01:16:40 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*byte;

	byte = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (byte[i] == (unsigned char)c)
			return (byte + i);
		i++;
	}
	return (NULL);
}
