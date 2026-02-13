/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strtrim.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:51 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:51 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

static int	strhas(char const c, char const *set)
{
	size_t	i;
	size_t	setlen;

	setlen = ft_strlen(set);
	i = 0;
	while (i < setlen)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	lp;
	size_t	rp;

	if (!s1 || !set)
		return (NULL);
	lp = 0;
	while (s1[lp] && (strhas(s1[lp], set)))
		lp++;
	if (s1[lp] == 0)
		return (ft_strdup(""));
	rp = ft_strlen(s1) - 1;
	while (rp > 0 && s1[rp] && (strhas(s1[rp], set)))
		rp--;
	return (ft_substr(s1, lp, rp - lp + 1));
}
