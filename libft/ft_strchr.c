/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:17 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:12:11 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *p, int ch)
{
	if (*p == (char)ch)
		return ((char *)p);
	while (*p++)
	{
		if (*p == (char)ch)
			return ((char *)p);
	}
	return (NULL);
}
