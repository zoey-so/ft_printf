/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers_csidu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 14:36:22 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 22:36:25 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(t_flags *flags, va_list args, int *len)
{
	char	*s;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	flags->s_len = (int)ft_strlen(s);
	if (flags->prec >= 0 && flags->prec < flags->s_len)
		flags->s_len = flags->prec;
	if (flags->width > flags->s_len)
	{
		*len += flags->width;
		if (flags->minus)
			write(1, s, flags->s_len);
		while (flags->width-- > flags->s_len)
			ft_putchar_fd(flags->padder, 1);
		if (!flags->minus)
			write(1, s, flags->s_len);
		return ;
	}
	write(1, s, flags->s_len);
	*len += flags->s_len;
}

void	print_char(t_flags *flags, va_list args, int *len)
{
	char	c;

	c = (char)va_arg(args, int);
	if (flags->width > 1)
	{
		*len += flags->width;
		if (flags->minus)
			ft_putchar_fd(c, 1);
		while ((flags->width)-- > 1)
			ft_putchar_fd(flags->padder, 1);
		if (!flags->minus)
			ft_putchar_fd(c, 1);
		return ;
	}
	ft_putchar_fd(c, 1);
	*len += 1;
}

void	print_dec(t_flags *flags, char *s, int *len)
{
	if (flags->prec > flags->s_len)
		flags->width -= flags->prec;
	else
		flags->width -= flags->s_len;
	*len += flags->s_len;
	if (flags->minus)
	{
		if (flags->sign_c && (*len)++)
			ft_putchar_fd(flags->sign_c, 1);
		while (flags->prec-- > flags->s_len && (*len)++)
			ft_putchar_fd('0', 1);
		write(1, s, flags->s_len);
	}
	while (flags->width-- > 0 && (*len)++)
		ft_putchar_fd(flags->padder, 1);
	if (!flags->minus)
	{
		if (flags->sign_c && (*len)++)
			ft_putchar_fd(flags->sign_c, 1);
		while (flags->prec-- > flags->s_len && (*len)++)
			ft_putchar_fd('0', 1);
		write(1, s, flags->s_len);
	}
	free(s);
}

void	print_int(t_flags *flags, va_list args, int *len)
{
	char	*s;
	long	nbr;

	nbr = (long int)va_arg(args, int);
	if (nbr == 0 && flags->prec == 0)
		s = ft_strdup("");
	else
		s = ft_itoa_u_base((((nbr >> 63) ^ (nbr)) - (nbr >> 63)), "0123456789");
	if (!s)
		return ;
	if (nbr < 0)
		flags->sign = 1;
	if (nbr < 0)
		flags->sign_c = '-';
	flags->s_len = (int)ft_strlen(s);
	if (flags->prec >= 0)
		flags->padder = ' ';
	if (flags->padder == '0')
		flags->prec = flags->width - flags->sign;
	if (flags->sign_c)
		flags->width--;
	print_dec(flags, s, len);
}

void	print_unsigned(t_flags *flags, va_list args, int *len)
{
	char	*s;
	long	nbr;

	nbr = (long int)va_arg(args, unsigned int);
	if (nbr == 0 && flags->prec == 0)
		s = ft_strdup("");
	else
		s = ft_itoa_u_base(nbr, "0123456789");
	if (!s)
		return ;
	flags->sign = 0;
	flags->sign_c = 0;
	flags->s_len = (int)ft_strlen(s);
	if (flags->prec >= 0)
		flags->padder = ' ';
	if (flags->padder == '0')
		flags->prec = flags->width;
	print_dec(flags, s, len);
}
