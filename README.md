*This project has been created as part of the 42 curriculum by smilch.*

# ft_printf

## Description

`ft_printf` is a custom implementation of the standard C library function `printf`. This project is part of the 42 school curriculum and aims to recreate the behavior of `printf` with a subset of its format specifiers and flags.

The implementation handles the following conversions:
- `%c` - Character
- `%s` - String
- `%p` - Pointer address (in hexadecimal)
- `%d` - Signed decimal integer
- `%i` - Signed integer (identical to `%d`)
- `%u` - Unsigned decimal integer
- `%x` - Hexadecimal (lowercase)
- `%X` - Hexadecimal (uppercase)
- `%%` - Percent sign

The following flags are supported:
- `-` (Left-justify within the field width)
- `0` (Zero-padding)
- `.` (Precision)
- `#` (Alternate form - adds `0x`/`0X` prefix for hex conversions)
- `+` (Always display sign for signed conversions)
- Space flag (Prefix positive numbers with a space)

Field minimum width is also fully supported across all conversions.

## Instructions

### Compilation

The project is compiled using the provided Makefile. To build the library:

```bash
make
```

This will generate `libftprintf.a` in the root directory.

### Cleaning

To remove object files:
```bash
make clean
```

To remove object files and the library:
```bash
make fclean
```

To rebuild everything from scratch:
```bash
make re
```

### Usage

To use `ft_printf` in your project, include the header file and link the library:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! The answer is %d.\n", "world", 42);
    return (0);
}
```

Compile with:
```bash
cc -I. your_program.c -L. -lftprintf
```

### Testing

The project includes a comprehensive test suite using Google Test. To run the tests:

```bash
make test
```

This will build and execute all test cases, comparing the output of `ft_printf` against the standard `printf` implementation.

## Algorithm and Data Structure

### Parsing Strategy

The implementation follows a two-phase approach:

1. **Parsing Phase**: The format string is scanned character by character. When a `%` is encountered, the parser extracts all flags, width, precision, and the conversion specifier into a `t_flags` structure.

2. **Printing Phase**: Based on the parsed specifier, the appropriate print function is called to render the output.

### Core Data Structure: `t_flags`

The `t_flags` structure stores all formatting information for a single conversion:

```c
typedef struct s_flags
{
    char    specifier;  // Conversion specifier (c, s, p, d, i, u, x, X)
    char    padder;     // Padding character (' ' or '0')
    short   minus;      // Left-justify flag
    short   prec;       // Precision value (-1 if not set)
    short   hash;       // Hash flag (#) - 0 or 2 (for 0x prefix)
    char    sign_c;     // Sign character ('+', '-', or ' ')
    short   sign;       // Sign flag
    short   width;      // Minimum field width
    int     s_len;      // Length of the converted string
} t_flags;
```

### Parsing Flow

1. **Flag Parsing** (`parse_flags`):
   - Iterates through the format string while characters match `-+ #0`
   - Sets corresponding flags in the `t_flags` structure
   - The `-` flag overrides `0` padding (enforced after parsing)

2. **Width Parsing** (`parse_width`):
   - Handles both literal numbers and the `*` (star) modifier
   - Negative width values are converted to positive and the `-` flag is set

3. **Precision Parsing** (`parse_precision`):
   - Parses the value after a `.` character
   - Supports both literal numbers and `*` modifier
   - Default precision is `-1` (not set)

4. **Specifier Extraction**:
   - The final character of the format specifier is stored as `specifier`
   - The format pointer is advanced past the specifier

### Print Functions

Each conversion specifier has its own print function:

- **`print_char`**: Handles `%c` - precision is ignored per standard behavior
- **`print_string`**: Handles `%s` - applies precision to limit string length
- **`print_int`**: Handles `%d` and `%i` - supports sign flags, precision, and zero-padding
- **`print_unsigned`**: Handles `%u` - similar to integer but without sign handling
- **`print_x`**: Handles `%x` and `%X` - supports hash flag for `0x`/`0X` prefix
- **`print_pointer`**: Handles `%p` - always prints `0x` prefix, special handling for NULL

### Flag Interaction Rules

The implementation respects standard `printf` flag precedence:
- The `-` flag overrides the `0` flag
- Precision overrides zero-padding for numeric conversions
- The `+` flag overrides the space flag
- The `#` flag has no effect on zero values for hex conversions
- Negative width values from `*` are converted to positive and set the `-` flag

### Return Value

`ft_printf` returns the total number of characters printed, excluding the terminating null byte, matching the behavior of the standard `printf`.

## Resources

### Documentation

- [printf(3) - Linux man page](https://man7.org/linux/man-pages/man3/printf.3.html)
- [The GNU C Library: Formatted Output](https://sourceware.org/glibc/manual/latest/html_node/Formatted-Output.html)
- [C99 Standard - §7.19.6.1 The fprintf function](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf)
- [C++ documentation](https://cplusplus.com/reference/cstdio/printf/)

### Others

- 42 Intra Knowledge Base
- [Understanding printf format specifiers](https://www.cprogramming.com/tutorial/printf-format-strings.html)
- [Variadic Functions in C](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)

### AI Usage

AI (DeepSeek) was utilized to assist in:

- Structuring and formatting this `README.md` document.
- Generating **repeatable, systematic test suites** for validation of the library functions based on cases listed by me.
  These test suites were written in C and used to compare the custom implementations against the original libc functions, doing my best to cover the edge cases. <br>
  **Note:** The test code is part of open repository on GitHub, but is not part of the project submission. The actual implementation of every function in the library was written manually by the project author.

## License

This project is provided as open‑source under the terms of the [MIT License](https://opensource.org/licenses/MIT). Feel free to use, modify, and distribute it in your own projects.

