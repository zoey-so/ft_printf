/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 21:45:48 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 21:47:28 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// skip flags other then precision specifier
// if there is asterix get the value from args
// otherwise read with atoi
// if width is negative get abs value and set minus flag
void	parse_width(const char **fmt, t_flags *flags, va_list args)
{
	if (**fmt == '*')
	{
		flags->width = va_arg(args, int);
		(*fmt)++;
	}
	else
	{
		flags->width = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->minus = 1;
	}
}

// go to dot
// if precision value is star - get it from args
// otherwise use ft_atoi to read the number
void	parse_precision(const char **fmt, t_flags *flags, va_list args)
{
	(*fmt)++;
	if (**fmt == '*')
	{
		flags->prec = va_arg(args, int);
		(*fmt)++;
	}
	else
	{
		flags->prec = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
}

// parse the flags
void	parse_flags(const char **fmt, t_flags *flags)
{
	while (**fmt && ft_strchr("-+ #0", **fmt))
	{
		if (**fmt == '-')
			flags->minus = 1;
		else if (**fmt == '0')
			flags->padder = '0';
		else if (**fmt == '+')
		{
			flags->sign = 1;
			flags->sign_c = '+';
		}
		else if (**fmt == ' ')
		{
			flags->sign = 1;
			if (flags->sign_c != '+')
				flags->sign_c = ' ';
		}
		else if (**fmt == '#')
			flags->hash = 2;
		(*fmt)++;
	}
}

// creating flags instance and setting them to default
// passing the format with args to parse flags
void	parse(const char **fmt, va_list args, int *len)
{
	t_flags	flags;

	flags.minus = 0;
	flags.padder = ' ';
	flags.prec = -1;
	flags.hash = 0;
	flags.sign_c = 0;
	flags.sign = 0;
	flags.specifier = 0;
	flags.width = 0;
	flags.s_len = 0;
	parse_flags(fmt, &flags);
	parse_width(fmt, &flags, args);
	if (**fmt == '.')
		parse_precision(fmt, &flags, args);
	if (flags.minus)
		flags.padder = ' ';
	flags.specifier = **fmt;
	if (flags.specifier)
	{
		(*fmt)++;
		print_flags(&flags, args, len);
	}
}
