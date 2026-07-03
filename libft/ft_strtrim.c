/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:17 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:12:48 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	const char	*beg;
	const char	*end;

	if (!s1)
		return (NULL);
	if (!set || !*set || !*s1)
		return (ft_strdup(s1));
	beg = s1;
	while (*beg && ft_strchr(set, *beg))
		beg++;
	if (*beg == '\0')
		return (ft_strdup("\0"));
	end = s1 + ft_strlen(s1) - 1;
	while (end > beg && ft_strchr(set, *end))
		end--;
	res = ft_substr(beg, 0, end - beg + 1);
	return (res);
}
