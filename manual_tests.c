#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>
int main()
{
	int a;
	int b;
	int x = 5;

	a = ft_printf("abc%sghj\n", "def");
	b = printf("abc%sghj\n", "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);


	a = ft_printf("abc%06sghj\n", "def");
	b = printf("abc%06sghj\n", "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);


	a = ft_printf("abc%-6sghj\n", "def");
	b = printf("abc%-6sghj\n", "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%.2sghj\n", "def");
	b = printf("abc%.2sghj\n", "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%-6.2sghj\n", "def");
	b = printf("abc%-6.2sghj\n", "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%-*.2sghj\n", 5, "def");
	b = printf("abc%-*.2sghj\n", 5, "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%*.*sghj\n", -5, 0, "def");
	b = printf("abc%*.*sghj\n", -5, 0, "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%*.0sghj\n", -5, "def");
	b = printf("abc%*.0sghj\n", -5, "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%*.sghj\n", -5, "def");
	b = printf("abc%*.sghj\n", -5, "def");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%-6.2sghj\n", NULL);
	b = printf("abc%-6.2sghj\n", NULL);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("abc%-6.cghj\n", 'A');
	b = printf("abc%-6.2cghj\n", 'A');
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%d|\n", 20);
	b = printf("|%d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%5d|\n", 20);
	b = printf("|%5d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%-5d|\n", -20);
	b = printf("|%-5d|\n", -20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%-+5d|\n", 20);
	b = printf("|%-+5d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%- 5d|\n", 20);
	b = printf("|%- 5d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%- 05d|\n", 20);
	b = printf("|%- 05d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|% 05d|\n", 20);
	b = printf("|% 05d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%+05d|\n", 20);
	b = printf("|%+05d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%+03d|\n", 20);
	b = printf("|%+03d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%+05.5d|\n", 20);
	b = printf("|%+05.5d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%-+ 5.4d|\n", 20);
	b = printf("|%-+ 5.4d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%+ 5.4d|\n", 20);
	b = printf("|%+ 5.4d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%-+ 5.6d|\n", 20);
	b = printf("|%-+ 5.6d|\n", 20);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%-+ 5.d|\n", 0);
	b = printf("|%-+ 5.d|\n", 0);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("|%-0+ 5.d|\n", 0);
	b = printf("|%-0+ 5.d|\n", 0);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	ft_printf("-----------------\nSPACE\n--------\n");
	a = ft_printf("71. |% d|\n", 42);          // | 42|
	b = printf("71. |% d|\n", 42);          // | 42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("72. |% d|\n", -42);         // |-42|
	b = printf("72. |% d|\n", -42);         // |-42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("73. |% 5d|\n", 42);         // |   42|
	b = printf("73. |% 5d|\n", 42);         // |   42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("74. |%- 5d|\n", 42);        // |42   |
	b = printf("74. |%- 5d|\n", 42);        // |42   |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("75. |% 05d|\n", 42);        // | 0042|  (space + zero)
	b = printf("75. |% 05d|\n", 42);        // | 0042|  (space + zero)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("76. |% +d|\n", 42);         // |+42|  (plus overrides space)
	b = printf("76. |% +d|\n", 42);         // |+42|  (plus overrides space)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("77. |% +d|\n", -42);        // |-42|
	b = printf("77. |% +d|\n", -42);        // |-42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("78. |% .5d|\n", 42);        // | 00042|
	b = printf("78. |% .5d|\n", 42);        // | 00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("79. |% d|\n", 0);           // | 0|
	b = printf("79. |% d|\n", 0);           // | 0|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("80. |% u|\n", 42);          // |42|  (space has no effect on unsigned)
	b = printf("80. |% u|\n", 42);          // |42|  (space has no effect on unsigned)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	ft_printf("-----------------\nPLUD SIGN\n--------\n");

	a = ft_printf("61. |%+d|\n", 42);          // |+42|
	b = printf("61. |%+d|\n", 42);          // |+42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("62. |%+d|\n", -42);         // |-42|
	b = printf("62. |%+d|\n", -42);         // |-42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("63. |%+5d|\n", 42);         // |  +42|
	b = printf("63. |%+5d|\n", 42);         // |  +42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("64. |%-+5d|\n", 42);        // |+42  |
	b = printf("64. |%-+5d|\n", 42);        // |+42  |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("65. |%+05d|\n", 42);        // |+0042|
	b = printf("65. |%+05d|\n", 42);        // |+0042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("66. |%+05d|\n", -42);       // |-0042|
	b = printf("66. |%+05d|\n", -42);       // |-0042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("67. |%+10.5d|\n", 42);      // |    +00042|
	b = printf("67. |%+10.5d|\n", 42);      // |    +00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("68. |%+d|\n", 0);           // |+0|
	b = printf("68. |%+d|\n", 0);           // |+0|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("69. |%+u|\n", 42);          // |42|  (plus has no effect on unsigned)
	b = printf("69. |%+u|\n", 42);          // |42|  (plus has no effect on unsigned)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	ft_printf("-----------------\nWIDTH PLUS PRECISION\n--------\n");

	a = ft_printf("40. |%10.5s|\n", "Hello World");   // |     Hello|
	b = printf("40. |%10.5s|\n", "Hello World");   // |     Hello|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("41. |%*.5s|\n", -10, "Hello World");  // |Hello     |
	b = printf("41. |%*.5s|\n", -10, "Hello World");  // |Hello     |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("42. |%8.3d|\n", 42);               // |   00042|
	b = printf("42. |%8.3d|\n", 42);               // |   00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("43. |%-8.3d|\n", 42);              // |00042   |
	b = printf("43. |%-8.3d|\n", 42);              // |00042   |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("44. |%08.3d|\n", 42);              // |00000042|  (zero ignored due to precision)
	b = printf("44. |%08.3d|\n", 42);              // |00000042|  (zero ignored due to precision)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("45. |%10.5d|\n", 42);              // |     00042|
	b = printf("45. |%10.5d|\n", 42);              // |     00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("46. |%-10.5d|\n", 42);             // |00042     |
	b = printf("46. |%-10.5d|\n", 42);             // |00042     |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("47. |%10.5x|\n", 255);             // |    000ff|
	b = printf("47. |%10.5x|\n", 255);             // |    000ff|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("48. |%-10.5x|\n", 255);            // |000ff     |
	b = printf("48. |%-10.5x|\n", 255);            // |000ff     |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("49. |%0+10.*d|\n", 5, 42);        // |     00042|
	b = printf("49. |%0+10.*d|\n", 5, 42);        // |     00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	ft_printf("-----------------\nPRECISION\n--------\n");
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("27. |%5.2s|\n", "Hello World");    // |Hello|
	b = printf("27. |%5.2s|\n", "Hello World");    // |Hello|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("28. |%.10s|\n", "Hello");         // |Hello|
	b = printf("28. |%.10s|\n", "Hello");         // |Hello|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("29. |%.0s|\n", "Hello");          // ||
	b = printf("29. |%.0s|\n", "Hello");          // ||
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("30. |%05.d|\n", 42);               // |00042|
	b = printf("30. |%05.d|\n", 42);               // |00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("31. |%.5d|\n", -42);              // |-00042|
	b = printf("31. |%.5d|\n", -42);              // |-00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("32. |%.3d|\n", 12345);            // |12345|  (precision smaller than number)
	b = printf("32. |%.3d|\n", 12345);            // |12345|  (precision smaller than number)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("33. |%+.0d|\n", 0);                // ||  (prints nothing for 0)
	b = printf("33. |%+.0d|\n", 0);                // ||  (prints nothing for 0)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("34. |%.0d|\n", 42);               // |42|
	b = printf("34. |%.0d|\n", 42);               // |42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("35. |%.5u|\n", 42);               // |00042|
	b = printf("35. |%.5u|\n", 42);               // |00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("38. |%.*s|\n", 3, "Hello");       // |Hel|
	b = printf("38. |%.*s|\n", 3, "Hello");       // |Hel|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("39. |%.*d|\n", 5, 42);            // |00042|
	b = printf("39. |%.*d|\n", 5, 42);            // |00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("10. |%u|\n", 42);           // |42|
	b = printf("10. |%u|\n", 42);           // |42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("11. |%u|\n", -42);          // |4294967254|
	b = printf("11. |%u|\n", -42);          // |4294967254|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("11. |%u|\n", -1);
	b = printf("11. |%u|\n", -1);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("14. |%%|\n");               // |%|
	b = printf("14. |%%|\n");               // |%|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("15. |%5d|\n", 42);          // |   42|
	b = printf("15. |%5d|\n", 42);          // |   42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("16. |%-5d|\n", 42);         // |42   |
	b = printf("16. |%-5d|\n", 42);         // |42   |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("17. |%05d|\n", 42);         // |00042|
	b = printf("17. |%05d|\n", 42);         // |00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("18. |%5d|\n", -42);         // |  -42|
	b = printf("18. |%5d|\n", -42);         // |  -42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("19. |%-5d|\n", -42);        // |-42  |
	b = printf("19. |%-5d|\n", -42);        // |-42  |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("20. |%05d|\n", -42);        // |-0042|  (zero flag with negative)
	b = printf("20. |%05d|\n", -42);        // |-0042|  (zero flag with negative)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("21. |%010s|\n", "Hello");    // |     Hello|
	b = printf("21. |%010s|\n", "Hello");    // |     Hello|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("22. |%-10s|\n", "Hello");   // |Hello     |
	b = printf("22. |%-10s|\n", "Hello");   // |Hello     |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("23. |%5c|\n", 'A');         // |    A|
	b = printf("23. |%5c|\n", 'A');         // |    A|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("24. |%-5c|\n", 'A');        // |A    |
	b = printf("24. |%-5c|\n", 'A');        // |A    |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("24. |%-15d|\n", INT_MIN);
	b = printf("24. |%-15d|\n", INT_MIN);
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("1.  |%c|\n", 'A');          // |A|
	b = printf("1.  |%c|\n", 'A');          // |A|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("2.  |%s|\n", "Hello");      // |Hello|
	b = printf("2.  |%s|\n", "Hello");      // |Hello|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("3.  |%s|\n", "");           // ||
	b = printf("3.  |%s|\n", "");           // ||
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("4.  |%10.2s|\n", NULL);         // |(null)|  (on most systems)
	b = printf("4.  |%10.2s|\n", NULL);         // |(null)|  (on most systems)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%.5p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%.5p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%.20p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%.20p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%#.20x|\n", 255);           // |0x7ff...| (address)
	b = printf("5.  |%#.20x|\n", 255);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%20p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%20p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%020p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%020p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%0#20x|\n", 255);           // |0x7ff...| (address)
	b = printf("5.  |%0#20x|\n", 255);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%020.5p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%020.5p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	b = printf("5.  |%0#20.5x|\n", 255);           // |0x7ff...| (address)
	b = printf("5.  |%0#20.5x|\n", 255);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%20p|\n", &x);           // |0x7ff...| (address)
	b = printf("5.  |%20p|\n", &x);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("5.  |%#20x|\n", 255);           // |0x7ff...| (address)
	b = printf("5.  |%#20x|\n", 255);           // |0x7ff...| (address)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("6.  |%p|\n", NULL);         // |(nil)| or |0x0|
	b = printf("6.  |%p|\n", NULL);         // |(nil)| or |0x0|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("7.  |%d|\n", 42);           // |42|
	b = printf("7.  |%d|\n", 42);           // |42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("8.  |%d|\n", -42);          // |-42|
	b = printf("8.  |%d|\n", -42);          // |-42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("9.  |%i|\n", 123);          // |123|
	b = printf("9.  |%i|\n", 123);          // |123|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("10. |%u|\n", 42);           // |42|
	b = printf("10. |%u|\n", 42);           // |42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("11. |%u|\n", -42);          // |4294967254|
	b = printf("11. |%u|\n", -42);          // |4294967254|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("12. |%x|\n", 255);          // |ff|
	b = printf("12. |%x|\n", 255);          // |ff|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("13. |%X|\n", 255);          // |FF|
	b = printf("13. |%X|\n", 255);          // |FF|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("14. |%%|\n");               // |%|
	b = printf("14. |%%|\n");               // |%|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("15. |%5d|\n", 42);          // |   42|
	b = printf("15. |%5d|\n", 42);          // |   42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("16. |%-5d|\n", 42);         // |42   |
	b = printf("16. |%-5d|\n", 42);         // |42   |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("17. |%05d|\n", 42);         // |00042|
	b = printf("17. |%05d|\n", 42);         // |00042|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("18. |%5d|\n", -42);         // |  -42|
	b = printf("18. |%5d|\n", -42);         // |  -42|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("19. |%-5d|\n", -42);        // |-42  |
	b = printf("19. |%-5d|\n", -42);        // |-42  |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("20. |%05d|\n", -42);        // |-0042|  (zero flag with negative)
	b = printf("20. |%05d|\n", -42);        // |-0042|  (zero flag with negative)
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("25. |%10x|\n", 255);        // |        ff|
	b = printf("25. |%10x|\n", 255);        // |        ff|
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("26. |%-10x|\n", 255);       // |ff        |
	b = printf("26. |%-10x|\n", 255);       // |ff        |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	a = ft_printf("27. |%-10c|\n", 150);       // |ff        |
	b = printf("27. |%-10c|\n", 150);       // |ff        |
	if (a != b)
		ft_printf("MISMATCH a = %d, b = %d\n", a, b);

	return 0;

	}
