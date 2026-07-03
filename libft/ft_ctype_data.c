/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:50:15 by smilch            #+#    #+#             */
/*   Updated: 2026/06/22 14:50:15 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// global lookup table for ctype functions - minimise calculation

const unsigned char	g_lup[1 + CTYPE_NUM_CHARS] = {
	0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, FT_S, FT_S, FT_S, FT_S, FT_S, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	FT_P | FT_S, FT_P, FT_P, FT_P,
	FT_P, FT_P, FT_P, FT_P,
	FT_P, FT_P, FT_P, FT_P,
	FT_P, FT_P, FT_P, FT_P,
	FT_D | FT_P, FT_D | FT_P, FT_D | FT_P, FT_D | FT_P,
	FT_D | FT_P, FT_D | FT_P, FT_D | FT_P, FT_D | FT_P,
	FT_D | FT_P, FT_D | FT_P, FT_P, FT_P,
	FT_P, FT_P, FT_P, FT_P,
	FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_P,
	FT_P, FT_P, FT_P, FT_P,
	FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_A | FT_P,
	FT_A | FT_P, FT_A | FT_P, FT_A | FT_P, FT_P,
	FT_P, FT_P, FT_P, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
