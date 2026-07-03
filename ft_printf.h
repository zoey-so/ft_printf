#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"
typedef struct	s_flags
{
	char	specifier;
	short	minus;
	short	zero;
	short	precision;
	short	hash;
	short	space;
	short	plus;
	short	width;
}		t_flags;

int ft_printf(const char *, ...);
#endif
