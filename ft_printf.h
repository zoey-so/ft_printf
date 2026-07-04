#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"
typedef struct	s_flags
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

int 	ft_printf(const char *, ...);
void	print_string(t_flags *flags, va_list args, int *len);
void	print_char(t_flags *flags, va_list args, int *len);
void	print_int(t_flags *flags, va_list args, int *len);
void	print_unsigned(t_flags *flags, va_list args, int *len);
void	print_pointer(t_flags *flags, va_list args, int *len);
void	print_xX(t_flags *flags, va_list args, int *len, char *base);
#endif
