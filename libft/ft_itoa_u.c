/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:15 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 13:04:26 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_u(long int n)
{
	char		*res;
	long int	nb;
	size_t		len;

	len = 0;
	nb = ((n >> 63) ^ (n)) - (n >> 63);
	while (++len && nb > 9)
		nb /= 10;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	nb = ((n >> 63) ^ (n)) - (n >> 63);
	while (len-- > 0)
	{
		res[len] = '0' + (nb % 10);
		nb /= 10;
	}
	return (res);
}
