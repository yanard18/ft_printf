/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strncmp.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:52 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:52 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i]
		&& n-- > 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
