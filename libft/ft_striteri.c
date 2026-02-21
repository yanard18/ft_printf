/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_striteri.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:53 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:54:41 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
