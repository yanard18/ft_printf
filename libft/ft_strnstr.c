/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strnstr.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:52 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:52 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	while (*big && len-- > 0)
	{
		if (len < len_little - 1)
			return (NULL);
		if (ft_strncmp(big, little, len_little) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
