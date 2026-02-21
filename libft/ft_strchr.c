/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strchr.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:50 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:50 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && (unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
