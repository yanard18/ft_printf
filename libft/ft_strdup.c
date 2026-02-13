/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strdup.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:52 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:52 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*res;

	slen = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * slen + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, slen + 1);
	return (res);
}
