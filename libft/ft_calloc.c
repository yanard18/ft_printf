/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_calloc.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:52 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:52 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			i;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	p = (unsigned char *)malloc(size * nmemb);
	if (!p)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
