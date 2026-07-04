/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:15 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 17:43:56 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_u_base(unsigned long long nbr, char *base)
{
	int				base_n;
	char			*res;
	long long int	nb;
	size_t			len;

	base_n = (int)ft_strlen(base);
	nb = nbr;
	len = 0;
	while (++len && nb > base_n - 1)
		nb /= base_n;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	nb = nbr;
	while (len-- > 0)
	{
		res[len] = base[nb % base_n];
		nb /= base_n;
	}
	return (res);
}
