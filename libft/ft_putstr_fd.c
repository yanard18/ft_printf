/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_putstr_fd.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:50 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:50 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned long	i;

	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}
