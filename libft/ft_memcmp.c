/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:15 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:10:53 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_cp;
	const unsigned char	*s2_cp;

	s1_cp = s1;
	s2_cp = s2;
	while (n)
	{
		if (*s1_cp++ != *s2_cp++)
			return (*--s1_cp - *--s2_cp);
		n--;
	}
	return (0);
}
