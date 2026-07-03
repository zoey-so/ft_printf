#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>

void	print_flags(t_flags *flags, va_list args, int *len)
{
	if (flags->specifier == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	(*len)++;
}

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
void parse_precision(const char **fmt, t_flags *flags, va_list args)
{
	(*fmt)++;
	if (**fmt == '*')
	{
		flags->precision = va_arg(args, int);
		(*fmt)++;
	}
	else
	{
		flags->precision = ft_atoi(*fmt);
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
			flags->zero = 1;
		else if (**fmt == ' ')
			flags->space = 1;
		else if (**fmt == '+')
			flags->plus = 1;
		else if (**fmt == '#')
			flags->hash = 1;
		(*fmt)++;
	}
}

// creating flags instance and setting them to default
// passing the format with args to parse flags
void	parse(const char **fmt, va_list args, int *len)
{
	t_flags	flags;

	flags.minus = 0;
	flags.zero = 0;
	flags.precision = -1;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.specifier = 0;
	flags.width = 0;

	parse_flags(fmt, &flags);
	parse_width(fmt, &flags, args);
	if (**fmt == '.')
		parse_precision(fmt, &flags, args);
	flags.specifier = **fmt;
	if (flags.specifier)
	{
		(*fmt)++;
		print_flags(&flags, args, len);
	}
}

int ft_printf(const char *fmt, ...)
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
