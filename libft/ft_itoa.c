/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_itoa.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dyanar <dyanar@student.42istanbul.com.tr>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/04 20:38:51 by dyanar			   #+#	  #+#			  */
/*	 Updated: 2026/02/04 20:41:15 by dyanar			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

static	char	*reverse(char *s)
{
	unsigned int	len;
	unsigned int	i;
	char			temp;

	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
		i++;
	}
	return (s);
}

static char	*alloc_nbrstr(long n)
{
	unsigned int	minus;
	unsigned int	len;

	minus = n < 0;
	if (n < 0)
		n *= -1;
	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return ((char *)malloc(sizeof(char) * (len + minus + 1)));
}

char	*ft_itoa(int n)
{
	char			*s;
	long			nbr;
	unsigned int	minus;
	unsigned int	i;

	nbr = n;
	minus = nbr < 0;
	s = alloc_nbrstr(nbr);
	if (nbr < 0)
		nbr *= -1;
	if (!s)
		return (NULL);
	i = 0;
	if (nbr == 0)
		s[i++] = '0';
	while (nbr > 0)
	{
		s[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (minus)
		s[i++] = '-';
	s[i] = 0;
	return (reverse(s));
}
