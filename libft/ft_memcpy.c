/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_memcpy.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:50 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:51 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
