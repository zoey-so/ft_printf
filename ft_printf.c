/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 14:36:42 by smilch            #+#    #+#             */
/*   Updated: 2026/07/04 21:49:34 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_flags(t_flags *flags, va_list args, int *len)
{
	if (flags->specifier == 's')
		print_string(flags, args, len);
	else if (flags->specifier == 'c')
		print_char(flags, args, len);
	else if (flags->specifier == 'i' || flags->specifier == 'd')
		print_int(flags, args, len);
	else if (flags->specifier == 'u')
		print_unsigned(flags, args, len);
	else if (flags->specifier == 'x')
		print_x(flags, args, len, "0123456789abcdef");
	else if (flags->specifier == 'X')
		print_x(flags, args, len, "0123456789ABCDEF");
	else if (flags->specifier == 'p')
		print_pointer(flags, args, len);
	else
	{
		ft_putchar_fd(flags->specifier, 1);
		*len += 1;
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			parse(&fmt, args, &len);
		}
		else
		{
			ft_putchar_fd(*(fmt++), 1);
			len++;
		}
	}
	va_end(args);
	return (len);
}
