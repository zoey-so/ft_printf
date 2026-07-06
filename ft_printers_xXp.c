/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers_xXp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 14:36:22 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 22:37:28 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex(t_flags *flags, int *len, char *base, char *s)
{
	if (flags->minus)
	{
		if (flags->hash)
		{
			ft_putchar_fd('0', 1);
			ft_putchar_fd(base[15] + 18, 1);
		}
		while (flags->prec-- > flags->s_len && (*len)++)
			ft_putchar_fd('0', 1);
		write(1, s, flags->s_len);
	}
	while (flags->width-- > 0 && (*len)++)
		ft_putchar_fd(flags->padder, 1);
	if (!flags->minus)
	{
		if (flags->hash)
		{
			ft_putchar_fd('0', 1);
			ft_putchar_fd(base[15] + 18, 1);
		}
		while (flags->prec-- > flags->s_len && (*len)++)
			ft_putchar_fd('0', 1);
		write(1, s, flags->s_len);
	}
	free(s);
}

void	print_x(t_flags *flags, va_list args, int *len, char *base)
{
	unsigned long long	nbr;
	char				*s;

	nbr = (unsigned long long)va_arg(args, unsigned int);
	if (nbr == 0)
		flags->hash = 0;
	if (flags->prec >= 0)
		flags->padder = ' ';
	*len += flags->hash;
	flags->width -= flags->hash;
	if (flags->padder == '0')
		flags->prec = flags->width;
	if (nbr == 0 && flags->prec == 0)
		s = ft_strdup("");
	else
		s = ft_itoa_u_base(nbr, base);
	if (!s)
		return ;
	flags->s_len = (int)ft_strlen(s);
	if (flags->prec > flags->s_len)
		flags->width -= flags->prec;
	else
		flags->width -= flags->s_len;
	*len += flags->s_len;
	print_hex(flags, len, base, s);
}

void	print_pointer(t_flags *flags, va_list args, int *len)
{
	unsigned long long	nbr;
	char				*s;

	nbr = (unsigned long long)va_arg(args, void *);
	flags->hash = 2;
	s = ft_itoa_u_base(nbr, "0123456789abcdef");
	if (flags->prec >= 0)
		flags->padder = ' ';
	if (nbr == 0)
		s = ft_strdup("(nil)");
	if (nbr == 0)
		flags->hash = 0;
	if (!s)
		return ;
	flags->width -= flags->hash;
	*len += flags->hash;
	if (flags->padder == '0')
		flags->prec = flags->width;
	flags->s_len = (int)ft_strlen(s);
	if (flags->prec > flags->s_len)
		flags->width -= flags->prec;
	else
		flags->width -= flags->s_len;
	*len += flags->s_len;
	print_hex(flags, len, "0123456789abcdef", s);
}
