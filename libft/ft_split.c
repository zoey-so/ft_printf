/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:17 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:12:09 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_strs(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		if (*s != c)
			n++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (n);
}

static char	**ft_fill_strs(char **res, const char *s, char c)
{
	const char	*w_end;
	int			i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			w_end = s;
			while (*w_end && *w_end != c)
				w_end++;
			res[i] = ft_substr(s, 0, w_end - s);
			if (!res[i++])
			{
				while (i > 0)
					free(res[--i]);
				free(res);
				return (NULL);
			}
			s = w_end;
		}
		while (*s && *s == c)
			s++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	strs_n;

	if (!s)
		return (NULL);
	strs_n = 0;
	if (*s)
		strs_n = 1;
	if (c)
		strs_n = ft_count_strs(s, c);
	res = (char **)malloc(sizeof(char *) * (strs_n + 1));
	if (!res)
		return (NULL);
	ft_fill_strs(res, s, c);
	res[strs_n] = NULL;
	return (res);
}
