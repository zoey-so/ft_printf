/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:17 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:12:23 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	r_len;
	char	*dest_cp;

	dest_cp = dest;
	while (*dest && dsize)
	{
		dest++;
		dsize--;
	}
	r_len = dest - dest_cp;
	if (!dsize)
		return (r_len + ft_strlen(src));
	while (*src)
	{
		if (dsize - 1)
		{
			*(dest++) = *src;
			dsize--;
		}
		src++;
		r_len++;
	}
	*dest = '\0';
	return (r_len);
}
