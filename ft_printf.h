/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 21:40:38 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 21:51:19 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_flags
{
	char	specifier;
	char	padder;
	short	minus;
	short	prec;
	short	hash;
	char	sign_c;
	short	sign;
	short	width;
	int		s_len;
}		t_flags;

int		ft_printf(const char *fmt, ...);
void	parse(const char **fmt, va_list args, int *len);
void	print_flags(t_flags *flags, va_list args, int *len);
void	print_string(t_flags *flags, va_list args, int *len);
void	print_char(t_flags *flags, va_list args, int *len);
void	print_int(t_flags *flags, va_list args, int *len);
void	print_unsigned(t_flags *flags, va_list args, int *len);
void	print_pointer(t_flags *flags, va_list args, int *len);
void	print_x(t_flags *flags, va_list args, int *len, char *base);
#endif
