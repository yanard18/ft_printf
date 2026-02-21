/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_memcmp.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:50 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:50 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;
	size_t			i;

	if (n == 0)
		return (0);
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	while (b1[i] == b2[i] && n-- > 1)
		i++;
	return (b1[i] - b2[i]);
}
