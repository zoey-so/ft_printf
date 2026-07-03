/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:17 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:12:26 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*src_cp;
	size_t		left_size;

	src_cp = src;
	left_size = size;
	if (left_size)
	{
		while (--left_size)
		{
			if (*src == '\0')
			{
				*dest++ = *src++;
				break ;
			}
			*(dest++) = *(src++);
		}
	}
	if (!left_size)
	{
		if (size)
			*dest = '\0';
		while (*src++)
			;
	}
	return (src - src_cp - 1);
}
