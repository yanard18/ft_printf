/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_split.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:52 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:38:52 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

static size_t	strcount(char const *s, char c)
{
	size_t	count;
	int		started;

	started = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !started)
			started = 1;
		else if (*s == c && started)
		{
			count++;
			started = 0;
		}
		s++;
		if (*s == 0 && started)
			count++;
	}
	return (count);
}

static char	**freeall(char **addr, size_t count)
{
	while (count--)
		free(addr[count]);
	free(addr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	long	len;
	size_t	count;

	res = (char **)malloc(sizeof(char *) * (strcount(s, c) + 1));
	if (!res)
		return (NULL);
	count = 0;
	while (*s)
	{
		len = 0;
		while (*s == c)
			s++;
		while (s[len] != c && s[len] != 0)
			len++;
		if (len > 0)
			res[count++] = ft_substr(s, 0, len);
		if (count > 0 && !res[count - 1])
			return (freeall(res, count - 1));
		s += len;
	}
	res[count] = NULL;
	return (res);
}
