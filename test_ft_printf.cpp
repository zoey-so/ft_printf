#include <gtest/gtest.h>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <functional>
#include <vector>
#include <utility>
#include <limits.h>

extern "C" {
    #define new n
    #include "libft.h"
    #include "ft_printf.h"
    #undef new
}

class PrintfTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_passed_ = true;
    }

    void TearDown() override {
    }

    // Capture standard printf output
    template<typename... Args>
    std::string std_printf(const char* format, Args... args) {
        return capture_printf(::printf, format, std::forward<Args>(args)...);
    }

    // Capture ft_printf output
    template<typename... Args>
    std::string ft_printf_capture(const char* format, Args... args) {
        return capture_printf(ft_printf, format, std::forward<Args>(args)...);
    }

    // Capture both and compare (NO return value check here)
    template<typename... Args>
    void assert_printf_equal(const char* format, Args... args) {
        // Capture standard printf
        std::string expected = capture_printf(::printf, format, std::forward<Args>(args)...);

        // Capture ft_printf
        std::string actual = capture_printf(ft_printf, format, std::forward<Args>(args)...);

        // Compare outputs
        EXPECT_EQ(expected, actual) << "Format: \"" << format << "\"";
    }

    // Separate function for return value testing
    template<typename... Args>
    void assert_return_value_equal(const char* format, Args... args) {
        // We need to capture BOTH the output AND the return value
        // Use a different approach - capture output and return value separately

        int ret_std, ret_ft;
        std::string output_std, output_ft;

        // Capture printf with return value
        {
            int pipefd[2];
            pipe(pipefd);
            int stdout_save = dup(STDOUT_FILENO);
            dup2(pipefd[1], STDOUT_FILENO);

            ret_std = ::printf(format, std::forward<Args>(args)...);
            fflush(stdout);

            dup2(stdout_save, STDOUT_FILENO);
            close(stdout_save);
            close(pipefd[1]);

            char buffer[8192] = {0};
            read(pipefd[0], buffer, sizeof(buffer) - 1);
            close(pipefd[0]);
            output_std = std::string(buffer);
        }

        // Capture ft_printf with return value
        {
            int pipefd[2];
            pipe(pipefd);
            int stdout_save = dup(STDOUT_FILENO);
            dup2(pipefd[1], STDOUT_FILENO);

            ret_ft = ft_printf(format, std::forward<Args>(args)...);
            fflush(stdout);

            dup2(stdout_save, STDOUT_FILENO);
            close(stdout_save);
            close(pipefd[1]);

            char buffer[8192] = {0};
            read(pipefd[0], buffer, sizeof(buffer) - 1);
            close(pipefd[0]);
            output_ft = std::string(buffer);
        }

        // Compare outputs
        EXPECT_EQ(output_std, output_ft) << "Format: \"" << format << "\"";
        // Compare return values
        EXPECT_EQ(ret_std, ret_ft) << "Return value mismatch for format: \"" << format << "\"";
    }

    // Generic capture function
    template<typename... Args>
    std::string capture_printf(int (*func)(const char*, ...), const char* format, Args... args) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return "";
        }

        int stdout_save = dup(STDOUT_FILENO);
        if (stdout_save == -1) {
            perror("dup");
            close(pipefd[0]);
            close(pipefd[1]);
            return "";
        }

        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            close(pipefd[0]);
            close(pipefd[1]);
            close(stdout_save);
            return "";
        }

        func(format, args...);
        fflush(stdout);

        dup2(stdout_save, STDOUT_FILENO);
        close(stdout_save);
        close(pipefd[1]);

        char buffer[8192] = {0};
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            return std::string(buffer);
        }
        return std::string("");
    }

    bool test_passed_;
};

// ============================================================================
// BASIC CONVERSION TESTS
// ============================================================================

TEST_F(PrintfTest, BasicChar) {
    assert_printf_equal("|%c|", 'A');
    assert_printf_equal("|%c|", 'Z');
    assert_printf_equal("|%c|", '0');
    assert_printf_equal("|%c|", '\n');
    assert_printf_equal("|%c|", '\t');
}

TEST_F(PrintfTest, BasicString) {
    assert_printf_equal("|%s|", "Hello");
    assert_printf_equal("|%s|", "World");
    assert_printf_equal("|%s|", "");
    assert_printf_equal("|%s|", "This is a longer string");
    assert_printf_equal("|%s|", "12345");
}

TEST_F(PrintfTest, BasicInteger) {
    assert_printf_equal("|%d|", 42);
    assert_printf_equal("|%d|", -42);
    assert_printf_equal("|%d|", 0);
    assert_printf_equal("|%d|", 2147483647);
    assert_printf_equal("|%d|", -2147483648);
}

TEST_F(PrintfTest, BasicUnsigned) {
    assert_printf_equal("|%u|", 42);
    assert_printf_equal("|%u|", 0);
    assert_printf_equal("|%u|", 4294967295u);
}

TEST_F(PrintfTest, BasicHex) {
    assert_printf_equal("|%x|", 255);
    assert_printf_equal("|%X|", 255);
    assert_printf_equal("|%x|", 0);
    assert_printf_equal("|%X|", 0);
    assert_printf_equal("|%x|", 0xabcdef);
    assert_printf_equal("|%X|", 0xABCDEF);
}

// ============================================================================
// WIDTH TESTS
// ============================================================================

TEST_F(PrintfTest, WidthInteger) {
    assert_printf_equal("|%5d|", 42);
    assert_printf_equal("|%10d|", 42);
    assert_printf_equal("|%1d|", 42);
    assert_printf_equal("|%5d|", -42);
    assert_printf_equal("|%10d|", -42);
}

TEST_F(PrintfTest, WidthString) {
    assert_printf_equal("|%10s|", "Hello");
    assert_printf_equal("|%20s|", "Hello");
    assert_printf_equal("|%2s|", "Hello");
}

TEST_F(PrintfTest, WidthChar) {
    assert_printf_equal("|%5c|", 'A');
    assert_printf_equal("|%10c|", 'B');
    assert_printf_equal("|%1c|", 'C');
}

// ============================================================================
// LEFT JUSTIFY TESTS (- flag)
// ============================================================================

TEST_F(PrintfTest, LeftJustifyInteger) {
    assert_printf_equal("|%-5d|", 42);
    assert_printf_equal("|%-10d|", 42);
    assert_printf_equal("|%-5d|", -42);
    assert_printf_equal("|%-10d|", -42);
}

TEST_F(PrintfTest, LeftJustifyString) {
    assert_printf_equal("|%-10s|", "Hello");
    assert_printf_equal("|%-20s|", "Hello");
    assert_printf_equal("|%-2s|", "Hello");
}

TEST_F(PrintfTest, LeftJustifyChar) {
    assert_printf_equal("|%-5c|", 'A');
    assert_printf_equal("|%-10c|", 'B');
}

// ============================================================================
// ZERO PADDING TESTS (0 flag)
// ============================================================================

TEST_F(PrintfTest, ZeroPaddingInteger) {
    assert_printf_equal("|%05d|", 42);
    assert_printf_equal("|%010d|", 42);
    assert_printf_equal("|%05d|", -42);
    assert_printf_equal("|%010d|", -42);
    assert_printf_equal("|%05d|", 0);
    assert_printf_equal("|%010d|", 0);
}

TEST_F(PrintfTest, ZeroPaddingHex) {
    assert_printf_equal("|%010x|", 255);
    assert_printf_equal("|%010X|", 255);
    assert_printf_equal("|%010x|", 0);
}

TEST_F(PrintfTest, ZeroPaddingChar) {
    assert_printf_equal("|%05c|", 'A');
    assert_printf_equal("|%010c|", 'B');
}

// ============================================================================
// PRECISION TESTS (.)
// ============================================================================

TEST_F(PrintfTest, PrecisionInteger) {
    assert_printf_equal("|%.5d|", 42);
    assert_printf_equal("|%.10d|", 42);
    assert_printf_equal("|%.3d|", 42);
    assert_printf_equal("|%.5d|", -42);
    assert_printf_equal("|%.10d|", -42);
    assert_printf_equal("|%.0d|", 0);
    assert_printf_equal("|%.0d|", 42);
}

TEST_F(PrintfTest, PrecisionString) {
    assert_printf_equal("|%.5s|", "Hello World");
    assert_printf_equal("|%.10s|", "Hello World");
    assert_printf_equal("|%.0s|", "Hello World");
    assert_printf_equal("|%.15s|", "Hello World");
}

TEST_F(PrintfTest, PrecisionHex) {
    assert_printf_equal("|%.8x|", 255);
    assert_printf_equal("|%.8X|", 255);
    assert_printf_equal("|%.0x|", 0);
    assert_printf_equal("|%.0x|", 255);
}

// ============================================================================
// WIDTH + PRECISION COMBINATIONS
// ============================================================================

TEST_F(PrintfTest, WidthAndPrecisionInteger) {
    assert_printf_equal("|%10.5d|", 42);
    assert_printf_equal("|%20.10d|", 42);
    assert_printf_equal("|%5.3d|", 42);
    assert_printf_equal("|%10.5d|", -42);
    assert_printf_equal("|%-10.5d|", 42);
    assert_printf_equal("|%-10.5d|", -42);
}

TEST_F(PrintfTest, WidthAndPrecisionString) {
    assert_printf_equal("|%10.5s|", "Hello World");
    assert_printf_equal("|%-10.5s|", "Hello World");
    assert_printf_equal("|%20.10s|", "Hello World");
    assert_printf_equal("|%5.3s|", "Hello World");
}

// ============================================================================
// HASH FLAG TESTS (#)
// ============================================================================

TEST_F(PrintfTest, HashFlagHex) {
    assert_printf_equal("|%#x|", 255);
    assert_printf_equal("|%#X|", 255);
    assert_printf_equal("|%#x|", 0);
    assert_printf_equal("|%#X|", 0);
    assert_printf_equal("|%#10x|", 255);
    assert_printf_equal("|%#010x|", 255);
}

// ============================================================================
// PLUS FLAG TESTS (+)
// ============================================================================

TEST_F(PrintfTest, PlusFlag) {
    assert_printf_equal("|%+d|", 42);
    assert_printf_equal("|%+d|", -42);
    assert_printf_equal("|%+d|", 0);
    assert_printf_equal("|%+5d|", 42);
    assert_printf_equal("|%+05d|", 42);
    assert_printf_equal("|%+10.5d|", 42);
}

// ============================================================================
// SPACE FLAG TESTS ( )
// ============================================================================

TEST_F(PrintfTest, SpaceFlag) {
    assert_printf_equal("|% d|", 42);
    assert_printf_equal("|% d|", -42);
    assert_printf_equal("|% d|", 0);
    assert_printf_equal("|% 5d|", 42);
    assert_printf_equal("|% 05d|", 42);
    assert_printf_equal("|% +d|", 42);
}

// ============================================================================
// POINTER TESTS
// ============================================================================

TEST_F(PrintfTest, Pointer) {
    int x = 42;
    int y = 0;
    int *ptr1 = &x;
    int *ptr2 = &y;

    assert_printf_equal("|%p|", ptr1);
    assert_printf_equal("|%p|", ptr2);
    assert_printf_equal("|%20p|", ptr1);
    assert_printf_equal("|%-20p|", ptr1);
    assert_printf_equal("|%020p|", ptr1);
}

TEST_F(PrintfTest, NullPointer) {
    void *null_ptr = NULL;
    assert_printf_equal("|%p|", (void*)null_ptr);
    assert_printf_equal("|%20p|", (void*)null_ptr);
    assert_printf_equal("|%-20p|", (void*)null_ptr);
}

// ============================================================================
// STAR WIDTH AND PRECISION TESTS (*)
// ============================================================================

TEST_F(PrintfTest, StarWidth) {
    assert_printf_equal("|%*d|", 10, 42);
    assert_printf_equal("|%*d|", -10, 42);
    assert_printf_equal("|%*s|", 10, "Hello");
    assert_printf_equal("|%*s|", -10, "Hello");
}

TEST_F(PrintfTest, StarPrecision) {
    assert_printf_equal("|%.*d|", 5, 42);
    assert_printf_equal("|%.*d|", -5, 42);
    assert_printf_equal("|%.*s|", 5, "Hello World");
    assert_printf_equal("|%.*s|", -5, "Hello World");
}

TEST_F(PrintfTest, StarWidthAndPrecision) {
    assert_printf_equal("|%*.*d|", 10, 5, 42);
    assert_printf_equal("|%*.*d|", -10, 5, 42);
    assert_printf_equal("|%*.*s|", 10, 5, "Hello World");
    assert_printf_equal("|%*.*s|", -10, -5, "Hello World");
}

// ============================================================================
// COMBINED FLAGS TESTS
// ============================================================================

TEST_F(PrintfTest, CombinedFlags) {
    assert_printf_equal("|%-#+ 010.5d|", 42);
    assert_printf_equal("|%-#+ 010.5d|", -42);
    assert_printf_equal("|%-# 010.5x|", 255);
    assert_printf_equal("|%-# 010.5X|", 255);
    assert_printf_equal("|%+05d|", 42);
    assert_printf_equal("|%+05d|", -42);
    assert_printf_equal("|%-+10.5d|", 42);
}

// ============================================================================
// MULTIPLE CONVERSIONS TESTS
// ============================================================================

TEST_F(PrintfTest, MultipleConversions) {
    assert_printf_equal("%d %s %x %c", 42, "test", 255, 'A');
    assert_printf_equal("%d + %d = %d", 10, 20, 30);
    assert_printf_equal("|%d| |%s| |%x| |%c|", 42, "hello", 255, 'Z');
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST_F(PrintfTest, EdgeCasesIntegers) {
    assert_printf_equal("%d", INT_MAX);
    assert_printf_equal("%d", INT_MIN);
    assert_printf_equal("%u", UINT_MAX);
    assert_printf_equal("%x", UINT_MAX);
    assert_printf_equal("%X", UINT_MAX);
}

TEST_F(PrintfTest, EdgeCasesPrecision) {
    assert_printf_equal("%.0d", 0);
    assert_printf_equal("%.0d", 42);
    assert_printf_equal("%.0x", 0);
    assert_printf_equal("%.0s", "Hello");
    assert_printf_equal("%.0c", 'A');
}

TEST_F(PrintfTest, EdgeCasesWidth) {
    assert_printf_equal("%0d", 42);
    assert_printf_equal("%00d", 42);
    assert_printf_equal("%0005d", 42);
    assert_printf_equal("%-05d", 42);
}

TEST_F(PrintfTest, EdgeCasesPercent) {
    assert_printf_equal("%%");
    assert_printf_equal("%% %%");
    assert_printf_equal("%%d", 42);
}

TEST_F(PrintfTest, EdgeCasesString) {
    assert_printf_equal("%s", (char*)NULL);
    assert_printf_equal("%10s", (char*)NULL);
    assert_printf_equal("%-10s", (char*)NULL);
    assert_printf_equal("%.5s", (char*)NULL);
}


// ============================================================================
// MULTIPLE CONVERSIONS WITH DIFFERENT TYPES
// ============================================================================

TEST_F(PrintfTest, MultipleConversionsBasic) {
    assert_printf_equal("%d %s %x %c", 42, "hello", 255, 'A');
    assert_printf_equal("%c %d %s %x", 'Z', 123, "world", 0xabc);
    assert_printf_equal("%s %c %x %d", "test", 'B', 0xff, -42);
    assert_printf_equal("%x %d %c %s", 0x123, -999, 'C', "foo");
}
TEST_F(PrintfTest, MultipleConversionsWithPointers) {
    int x = 42;
    int y = 123;
    int z = 0;

    assert_printf_equal("%p %d %s", &x, 42, "hello");
    assert_printf_equal("%d %p %s", 123, &y, "world");
    assert_printf_equal("%s %d %p", "test", 456, &z);
    assert_printf_equal("%p %p %p", &x, &y, &z);
}

TEST_F(PrintfTest, MultipleConversionsWithUnsigned) {
    assert_printf_equal("%u %d %x", 4294967295u, -42, 255);
    assert_printf_equal("%d %u %X", 123, 4294967295u, 0xABCDEF);
    assert_printf_equal("%x %X %u", 0xabc, 0xDEF, 123456);
}

// ============================================================================
// MULTIPLE CONVERSIONS WITH WIDTH
// ============================================================================

TEST_F(PrintfTest, MultipleConversionsWidth) {
    assert_printf_equal("|%5d|%10s|%3c|", 42, "hello", 'A');
    assert_printf_equal("|%10d|%5s|%8c|", 123, "world", 'B');
    assert_printf_equal("|%3d|%15s|%6c|", -42, "test", 'C');
    assert_printf_equal("|%8d|%4s|%12c|", 0, "foo", 'D');
}

TEST_F(PrintfTest, MultipleConversionsLeftJustify) {
    assert_printf_equal("|%-5d|%-10s|%-3c|", 42, "hello", 'A');
    assert_printf_equal("|%-10d|%-5s|%-8c|", 123, "world", 'B');
    assert_printf_equal("|%-3d|%-15s|%-6c|", -42, "test", 'C');
}

TEST_F(PrintfTest, MultipleConversionsZeroPadding) {
    assert_printf_equal("|%05d|%010s|%03c|", 42, "hello", 'A');
    assert_printf_equal("|%010d|%05s|%08c|", 123, "world", 'B');
    assert_printf_equal("|%05d|%010x|%08X|", 42, 255, 255);
}

// ============================================================================
// MULTIPLE CONVERSIONS WITH PRECISION
// ============================================================================

TEST_F(PrintfTest, MultipleConversionsPrecision) {
    assert_printf_equal("|%.5d|%.3s|%.2c|", 42, "hello", 'A');
    assert_printf_equal("|%.10d|%.5s|%.1c|", 123, "world", 'B');
    assert_printf_equal("|%.3d|%.10s|%.0c|", -42, "test", 'C');
    assert_printf_equal("|%.8d|%.4s|%.6c|", 0, "foobar", 'D');
}

TEST_F(PrintfTest, MultipleConversionsWidthAndPrecision) {
    assert_printf_equal("|%10.5d|%15.10s|%8.3c|", 42, "hello world", 'A');
    assert_printf_equal("|%8.3d|%12.8s|%10.5c|", 123, "test string", 'B');
    assert_printf_equal("|%15.10d|%10.5s|%12.8c|", -42, "foo bar", 'C');
    assert_printf_equal("|%5.2d|%20.15s|%6.4c|", 0, "very long string", 'D');
}

TEST_F(PrintfTest, MultipleConversionsLeftJustifyWidthPrecision) {
    assert_printf_equal("|%-10.5d|%-15.10s|%-8.3c|", 42, "hello world", 'A');
    assert_printf_equal("|%-8.3d|%-12.8s|%-10.5c|", 123, "test string", 'B');
    assert_printf_equal("|%-15.10d|%-10.5s|%-12.8c|", -42, "foo bar", 'C');
}

// ============================================================================
// MULTIPLE CONVERSIONS WITH HASH FLAG (#)
// ============================================================================

TEST_F(PrintfTest, MultipleConversionsHash) {
    assert_printf_equal("%#x %#X %d", 255, 255, 42);
    assert_printf_equal("%d %#x %#X", 123, 0xabc, 0xDEF);
    assert_printf_equal("%#x %d %#X", 0, 42, 0);
    assert_printf_equal("%#10x %#-10X %d", 255, 255, 42);
    assert_printf_equal("%#010x %#-10X %d", 255, 255, 42);
}

// ============================================================================
// MULTIPLE CONVERSIONS WITH PLUS (+) AND SPACE ( ) FLAGS
// ============================================================================

TEST_F(PrintfTest, MultipleConversionsPlusSpace) {
    assert_printf_equal("%+d % d %+d", 42, 42, -42);
    assert_printf_equal("% d %+d % d", 123, -123, 456);
    assert_printf_equal("%+5d % 5d %+10d", 42, 42, -42);
    assert_printf_equal("%-+5d %- 5d %+d", 42, 42, -42);
    assert_printf_equal("%+05d % 05d %+10.5d", 42, 42, -42);
}
TEST_F(PrintfTest, MultipleConversionsPlusSpaceMixed) {
    assert_printf_equal("%+d %d % d %+d", 42, 123, 456, -42);
    assert_printf_equal("% d %+d %d % d", 123, -123, 456, -456);
    assert_printf_equal("%+d % d %+d % d", 1, 2, -3, -4);
}

// ============================================================================
// MIXED WIDTH, PRECISION, AND FLAGS
// ============================================================================

TEST_F(PrintfTest, MixedWidthPrecisionFlags) {
    assert_printf_equal("|%+010.5d|%-#15.10x|%-+10.5d|", 42, 255, 42);
    assert_printf_equal("|%#010x|%+10.5d|%-#15.10X|", 255, -42, 255);
    assert_printf_equal("|%-+10.5d|%#010x|%+10.5d|", 42, 0, -42);
    assert_printf_equal("|%-#15.10x|%-+10.5d|%#010X|", 255, 42, 255);
}

TEST_F(PrintfTest, MixedFlagsAllConversions) {
    assert_printf_equal(
        "%+d % d %#x %#X %u %c %s %p",
        42, 42, 255, 255, 123, 'A', "hello", (void*)0x12345
    );

    int x = 42;
    assert_printf_equal(
        "%+10.5d %-#15.10x %-+10.5d %#010X %u %c %-20s %p",
        42, 255, 42, 255, 123, 'B', "world", &x
    );
}

// ============================================================================
// MULTIPLE CONVERSIONS WITH STAR WIDTH AND PRECISION
// ============================================================================

TEST_F(PrintfTest, MultipleStarWidth) {
    assert_printf_equal("%*d %*d %*s", 5, 42, 10, 123, 8, "hello");
    assert_printf_equal("%*d %*s %*c", 3, 42, 15, "world", 6, 'A');
    assert_printf_equal("%*d %*d %*d", -5, 42, -10, 123, -8, 456);
}

TEST_F(PrintfTest, MultipleStarPrecision) {
    assert_printf_equal("%.*d %.*s %.*c", 5, 42, 3, "hello", 2, 'A');
    assert_printf_equal("%.*d %.*s %.*x", 10, 123, 5, "world", 8, 255);
    assert_printf_equal("%.*d %.*s %.*X", -5, 42, -3, "hello", -8, 255);
}

TEST_F(PrintfTest, MultipleStarWidthAndPrecision) {
    assert_printf_equal("%*.*d %*.*s %*.*c", 10, 5, 42, 15, 10, "hello", 8, 3, 'A');
    assert_printf_equal("%*.*d %*.*x %*.*X", 8, 3, 123, 12, 8, 255, 10, 5, 255);
    assert_printf_equal("%-*.*d %-*.*s %-*.*c", 10, 5, 42, 15, 10, "world", 8, 3, 'B');
}

// ============================================================================
// COMPLEX MIXED CONVERSIONS WITH BOUNDARY VALUES
// ============================================================================

TEST_F(PrintfTest, ComplexBoundaryValues) {
    assert_printf_equal(
        "%d %u %x %X %c %s %p",
        INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 'A', "test", (void*)0x12345
    );

    assert_printf_equal(
        "%d %d %u %x %X",
        INT_MIN, INT_MAX, UINT_MAX, 0, 0
    );

    assert_printf_equal(
        "%+d %+d % d % u %#x %#X",
        INT_MAX, INT_MIN, 42, 123, 255, 255
    );
}

TEST_F(PrintfTest, ComplexWithNullStrings) {
    char *null_str = NULL;
    assert_printf_equal("%s %s %s", "hello", null_str, "world");
    assert_printf_equal("%10s %-10s %.5s", null_str, null_str, null_str);
    assert_printf_equal("%*.*s %-*.*s", 10, 5, null_str, 15, 10, null_str);
}

// ============================================================================
// RANDOM COMBINATIONS
// ============================================================================

TEST_F(PrintfTest, RandomCombinations1) {
    assert_printf_equal(
        "|%+10.5d|%-#15.10x|%-+10.5d|%#010X|%u|%c|%-20.10s|%p|",
        42, 255, -42, 255, 123, 'A', "hello world", (void*)0x12345
    );
}

TEST_F(PrintfTest, RandomCombinations2) {
    int x = 42;
    assert_printf_equal(
        "%-+010.5d %#015x %+10.5d %#-10X %u %c %-20s %p %d",
        42, 255, -42, 255, 123, 'B', "test string", &x, 999
    );
}

TEST_F(PrintfTest, RandomCombinations3) {
    assert_printf_equal(
        "%*.*d %*.*s %*.*c %*.*x %*.*X",
        10, 5, 42, 15, 10, "hello", 8, 3, 'A', 12, 8, 255, 10, 5, 255
    );
}

TEST_F(PrintfTest, RandomCombinations4) {
    assert_printf_equal(
        "|%-10.5d|%+10.5d|%-#15.10x|%#010X|%+d|% d|%u|%c|%-20.10s|%p|",
        42, -42, 255, 255, 123, 123, 456, 'C', "mixed types", (void*)0xABCD
    );
}

TEST_F(PrintfTest, RandomCombinations5) {
    int x = 42;
    int y = 123;
    assert_printf_equal(
        "%#-20d % 10.5s %-0#25.4x %c %p %u %X %+d % d %#x",
        42, "test", 255, 'A', &x, 123, 0xDEF, 456, 456, 255
    );
    assert_printf_equal(
        "%d %s %x %c %p %u %X %+d % d %#x",
        -42, "another", 0xabc, 'Z', &y, 456, 0x123, -123, -123, 0
    );
}

// ============================================================================
// MULTIPLE CONVERSIONS WITH PERCENT SIGN
// ============================================================================

TEST_F(PrintfTest, MultipleWithPercent) {
    assert_printf_equal("%d %% %s %% %x", 42, "hello", 255);
    assert_printf_equal("%% %d %% %s %% %x %%", 42, "world", 255);
    assert_printf_equal("%d%%%s%%%x", 42, "test", 255);
    assert_printf_equal("%% %+d %% %#x %% %c %%", 42, 255, 'A');
}

// ============================================================================
// VERY LONG COMPLEX STRINGS
// ============================================================================

TEST_F(PrintfTest, VeryLongComplex) {
    assert_printf_equal(
        "Formatted: %+10.5d, Hex: %-#15.10x, Upper: %#010X, "
        "Unsigned: %u, Char: %c, String: %-20.10s, Pointer: %p, "
        "Percent: %%, Another: %d, Hex2: %#x",
        42, 255, 255, 123, 'A', "hello world", (void*)0x12345, -42, 0xABC
    );
}

// ============================================================================
// EDGE CASES WITH COMBINATIONS
// ============================================================================

TEST_F(PrintfTest, EdgeCasesCombined) {
    // Zero precision with mixed types
    assert_printf_equal("%.0d %.0x %.0s %.0c", 0, 0, "hello", 'A');
    assert_printf_equal("%.0d %.0x %.0s %.0c", 42, 255, "world", 'B');

    // Width 0 with mixed types
    assert_printf_equal("%0d %0x %0s %0c", 42, 255, "test", 'A');
    assert_printf_equal("%00d %00x %00s %00c", 42, 255, "hello", 'B');

    // Minus flags with mixed types
    assert_printf_equal("%-020d %0-20x %0-20s %-020c", 42, 255, "world", 'A');
    assert_printf_equal("%0-10.5d %-#010x %-20s %-5c", 42, 255, "test", 'B');
	int a = 5;
	assert_printf_equal("%-05d %-#030p %-20s %-5c", 42, &a, "test", 'B');
}

// ============================================================================
// ALL CONVERSIONS WITH ALL FLAGS COMBINED
// ============================================================================

TEST_F(PrintfTest, AllConversionsAllFlags) {
    int x = 42;
    assert_printf_equal(
        "%c %s %p %d %i %u %x %X %%",
        'A', "test", &x, 42, -42, 123, 255, 255
    );

    assert_printf_equal(
        "%+d % d %#x %#X %u %c %s %p %%",
        42, 42, 255, 255, 123, 'B', "hello", &x
    );

    assert_printf_equal(
        "%-10.5d %+10.5d %-#15.10x %#010X %-20.10s %p",
        42, -42, 255, 255, "world", &x
    );
}

// ============================================================================
// RETURN VALUE COMPLEX TESTS
// ============================================================================

TEST_F(PrintfTest, ReturnValueComplex) {
    assert_return_value_equal("%d %s %x %c", 42, "test", 255, 'A');
    assert_return_value_equal("%+d % d %#x %#X", 42, 42, 255, 255);
    assert_return_value_equal("%10.5d %-15.10s %#010x", 42, "hello", 255);
    assert_return_value_equal("%*.*d %*.*s", 10, 5, 42, 15, 10, "world");
    assert_return_value_equal(
        "%d %s %x %c %p %u %X %+d % d %#x",
        42, "test", 255, 'A', (void*)0x123, 123, 0xDEF, 456, 456, 255
    );
}

// ============================================================================
// STRESS TEST - MANY CONVERSIONS
// ============================================================================

TEST_F(PrintfTest, StressTestManyConversions) {
    assert_printf_equal(
        "%-12.3d ffwfwfgrw %020dwgwrrgrwggr grwgw  %#49.1drfjjfjsjff \n %+-3d \tfdadfdfafd\t%dffdwgwwrg %drgwrwgw %dgrwrg %d %dwrgwgrrwrwvw %dfg4244g242g24g2 %s-+#-%s%-020s%s+ #%+20.2s48i4284%s %s %s %s %s %c %c %c %12.43c %c %c %c %c %c %c %x %x %x %x %x %X %X-54=+%-020.2X0- %Xfqfejiefjifejf%X",
        1000, -22131, 345522, -43535, 5, 6, 79000, 800000, 912, 101, "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',  132245, 315432, 34553, 1, -1, 643431, 7566664, 999999, 10000, 0
    );
}


// ============================================================================
// RETURN VALUE TESTS - SEPARATE!
// ============================================================================

TEST_F(PrintfTest, ReturnValue) {
	int x = 42;
    int y = 0;
    int *ptr1 = &x;
    int *ptr2 = &y;
	void *null_ptr = NULL;
	char *null_str = NULL;
	char z[] = "djsjs";
	long long a = 5;

    assert_return_value_equal("|%c|", 'A');
    assert_return_value_equal("|%c|", 'Z');
    assert_return_value_equal("|%c|", '0');
    assert_return_value_equal("|%c|", '\n');
    assert_return_value_equal("|%c|", '\t');
    assert_return_value_equal("|%s|", "Hello");
    assert_return_value_equal("|%s|", "World");
    assert_return_value_equal("|%s|", "");
    assert_return_value_equal("|%s|", "This is a longer string");
    assert_return_value_equal("|%s|", "12345");
    assert_return_value_equal("|%d|", 42);
    assert_return_value_equal("|%d|", -42);
    assert_return_value_equal("|%d|", 0);
    assert_return_value_equal("|%d|", 2147483647);
    assert_return_value_equal("|%d|", -2147483648);
    assert_return_value_equal("|%u|", 42);
    assert_return_value_equal("|%u|", 0);
    assert_return_value_equal("|%u|", 4294967295u);
    assert_return_value_equal("|%x|", 255);
    assert_return_value_equal("|%X|", 255);
    assert_return_value_equal("|%x|", 0);
    assert_return_value_equal("|%X|", 0);
    assert_return_value_equal("|%x|", 0xabcdef);
    assert_return_value_equal("|%X|", 0xABCDEF);
    assert_return_value_equal("|%5d|", 42);
    assert_return_value_equal("|%10d|", 42);
    assert_return_value_equal("|%1d|", 42);
    assert_return_value_equal("|%5d|", -42);
    assert_return_value_equal("|%10d|", -42);
    assert_return_value_equal("|%10s|", "Hello");
    assert_return_value_equal("|%20s|", "Hello");
    assert_return_value_equal("|%2s|", "Hello");
    assert_return_value_equal("|%5c|", 'A');
    assert_return_value_equal("|%10c|", 'B');
    assert_return_value_equal("|%1c|", 'C');
    assert_return_value_equal("|%-5d|", 42);
    assert_return_value_equal("|%-10d|", 42);
    assert_return_value_equal("|%-5d|", -42);
    assert_return_value_equal("|%-10d|", -42);
    assert_return_value_equal("|%-10s|", "Hello");
    assert_return_value_equal("|%-20s|", "Hello");
    assert_return_value_equal("|%-2s|", "Hello");
    assert_return_value_equal("|%-5c|", 'A');
    assert_return_value_equal("|%-10c|", 'B');
    assert_return_value_equal("|%05d|", 42);
    assert_return_value_equal("|%010d|", 42);
    assert_return_value_equal("|%05d|", -42);
    assert_return_value_equal("|%010d|", -42);
    assert_return_value_equal("|%05d|", 0);
    assert_return_value_equal("|%010d|", 0);
    assert_return_value_equal("|%010x|", 255);
    assert_return_value_equal("|%010X|", 255);
    assert_return_value_equal("|%010x|", 0);
    assert_return_value_equal("|%05c|", 'A');
    assert_return_value_equal("|%010c|", 'B');
    assert_return_value_equal("|%.5d|", 42);
    assert_return_value_equal("|%.10d|", 42);
    assert_return_value_equal("|%.3d|", 42);
    assert_return_value_equal("|%.5d|", -42);
    assert_return_value_equal("|%.10d|", -42);
    assert_return_value_equal("|%.0d|", 0);
    assert_return_value_equal("|%.0d|", 42);
    assert_return_value_equal("|%.5s|", "Hello World");
    assert_return_value_equal("|%.10s|", "Hello World");
    assert_return_value_equal("|%.0s|", "Hello World");
    assert_return_value_equal("|%.15s|", "Hello World");
    assert_return_value_equal("|%.8x|", 255);
    assert_return_value_equal("|%.8X|", 255);
    assert_return_value_equal("|%.0x|", 0);
    assert_return_value_equal("|%.0x|", 255);
    assert_return_value_equal("|%10.5d|", 42);
    assert_return_value_equal("|%20.10d|", 42);
    assert_return_value_equal("|%5.3d|", 42);
    assert_return_value_equal("|%10.5d|", -42);
    assert_return_value_equal("|%-10.5d|", 42);
    assert_return_value_equal("|%-10.5d|", -42);
    assert_return_value_equal("|%10.5s|", "Hello World");
    assert_return_value_equal("|%-10.5s|", "Hello World");
    assert_return_value_equal("|%20.10s|", "Hello World");
    assert_return_value_equal("|%5.3s|", "Hello World");
    assert_return_value_equal("|%#x|", 255);
    assert_return_value_equal("|%#X|", 255);
    assert_return_value_equal("|%#x|", 0);
    assert_return_value_equal("|%#X|", 0);
    assert_return_value_equal("|%#10x|", 255);
    assert_return_value_equal("|%#010x|", 255);
    assert_return_value_equal("|%+d|", 42);
    assert_return_value_equal("|%+d|", -42);
    assert_return_value_equal("|%+d|", 0);
    assert_return_value_equal("|%+5d|", 42);
    assert_return_value_equal("|%+05d|", 42);
    assert_return_value_equal("|%+10.5d|", 42);
    assert_return_value_equal("|% d|", 42);
    assert_return_value_equal("|% d|", -42);
    assert_return_value_equal("|% d|", 0);
    assert_return_value_equal("|% 5d|", 42);
    assert_return_value_equal("|% 05d|", 42);
    assert_return_value_equal("|% +d|", 42);
    assert_return_value_equal("|%p|", ptr1);
    assert_return_value_equal("|%p|", ptr2);
    assert_return_value_equal("|%20p|", ptr1);
    assert_return_value_equal("|%-20p|", ptr1);
    assert_return_value_equal("|%020p|", ptr1);
    assert_return_value_equal("|%p|", (void*)null_ptr);
    assert_return_value_equal("|%20p|", (void*)null_ptr);
    assert_return_value_equal("|%-20p|", (void*)null_ptr);
    assert_return_value_equal("|%*d|", 10, 42);
    assert_return_value_equal("|%*d|", -10, 42);
    assert_return_value_equal("|%*s|", 10, "Hello");
    assert_return_value_equal("|%*s|", -10, "Hello");
    assert_return_value_equal("|%.*d|", 5, 42);
    assert_return_value_equal("|%.*d|", -5, 42);
    assert_return_value_equal("|%.*s|", 5, "Hello World");
    assert_return_value_equal("|%.*s|", -5, "Hello World");
    assert_return_value_equal("|%*.*d|", 10, 5, 42);
    assert_return_value_equal("|%*.*d|", -10, 5, 42);
    assert_return_value_equal("|%*.*s|", 10, 5, "Hello World");
    assert_return_value_equal("|%*.*s|", -10, -5, "Hello World");
    assert_return_value_equal("|%-#+ 010.5d|", 42);
    assert_return_value_equal("|%-#+ 010.5d|", -42);
    assert_return_value_equal("|%-# 010.5x|", 255);
    assert_return_value_equal("|%-# 010.5X|", 255);
    assert_return_value_equal("|%+05d|", 42);
    assert_return_value_equal("|%+05d|", -42);
    assert_return_value_equal("|%-+10.5d|", 42);
    assert_return_value_equal("%d %s %x %c", 42, "test", 255, 'A');
    assert_return_value_equal("%d + %d = %d", 10, 20, 30);
    assert_return_value_equal("|%d| |%s| |%x| |%c|", 42, "hello", 255, 'Z');
    assert_return_value_equal("%d", INT_MAX);
    assert_return_value_equal("%d", INT_MIN);
    assert_return_value_equal("%u", UINT_MAX);
    assert_return_value_equal("%x", UINT_MAX);
    assert_return_value_equal("%X", UINT_MAX);
    assert_return_value_equal("%.0d", 0);
    assert_return_value_equal("%.0d", 42);
    assert_return_value_equal("%.0x", 0);
    assert_return_value_equal("%.0s", "Hello");
    assert_return_value_equal("%.0c", 'A');
    assert_return_value_equal("%0d", 42);
    assert_return_value_equal("%00d", 42);
    assert_return_value_equal("%0005d", 42);
    assert_return_value_equal("%-05d", 42);
    assert_return_value_equal("%%");
    assert_return_value_equal("%% %%");
    assert_return_value_equal("%%d", 42);
    assert_return_value_equal("%s", (char*)NULL);
    assert_return_value_equal("%10s", (char*)NULL);
    assert_return_value_equal("%-10s", (char*)NULL);
    assert_return_value_equal("%.5s", (char*)NULL);
    assert_return_value_equal("|%c|", 'A');
    assert_return_value_equal("|%c|", 'Z');
    assert_return_value_equal("|%c|", '0');
    assert_return_value_equal("|%c|", '\n');
    assert_return_value_equal("|%c|", '\t');
    assert_return_value_equal("|%s|", "Hello");
    assert_return_value_equal("|%s|", "World");
    assert_return_value_equal("|%s|", "");
    assert_return_value_equal("|%s|", "This is a longer string");
    assert_return_value_equal("|%s|", "12345");
    assert_return_value_equal("|%d|", 42);
    assert_return_value_equal("|%d|", -42);
    assert_return_value_equal("|%d|", 0);
    assert_return_value_equal("|%d|", 2147483647);
    assert_return_value_equal("|%d|", -2147483648);
    assert_return_value_equal("|%u|", 42);
    assert_return_value_equal("|%u|", 0);
    assert_return_value_equal("|%u|", 4294967295u);
    assert_return_value_equal("|%x|", 255);
    assert_return_value_equal("|%X|", 255);
    assert_return_value_equal("|%x|", 0);
    assert_return_value_equal("|%X|", 0);
    assert_return_value_equal("|%x|", 0xabcdef);
    assert_return_value_equal("|%X|", 0xABCDEF);
    assert_return_value_equal("|%5d|", 42);
    assert_return_value_equal("|%10d|", 42);
    assert_return_value_equal("|%1d|", 42);
    assert_return_value_equal("|%5d|", -42);
    assert_return_value_equal("|%10d|", -42);
    assert_return_value_equal("|%10s|", "Hello");
    assert_return_value_equal("|%20s|", "Hello");
    assert_return_value_equal("|%2s|", "Hello");
    assert_return_value_equal("|%5c|", 'A');
    assert_return_value_equal("|%10c|", 'B');
    assert_return_value_equal("|%1c|", 'C');
    assert_return_value_equal("|%-5d|", 42);
    assert_return_value_equal("|%-10d|", 42);
    assert_return_value_equal("|%-5d|", -42);
    assert_return_value_equal("|%-10d|", -42);
    assert_return_value_equal("|%-10s|", "Hello");
    assert_return_value_equal("|%-20s|", "Hello");
    assert_return_value_equal("|%-2s|", "Hello");
    assert_return_value_equal("|%-5c|", 'A');
    assert_return_value_equal("|%-10c|", 'B');
    assert_return_value_equal("|%05d|", 42);
    assert_return_value_equal("|%010d|", 42);
    assert_return_value_equal("|%05d|", -42);
    assert_return_value_equal("|%010d|", -42);
    assert_return_value_equal("|%05d|", 0);
    assert_return_value_equal("|%010d|", 0);
    assert_return_value_equal("|%010x|", 255);
    assert_return_value_equal("|%010X|", 255);
    assert_return_value_equal("|%010x|", 0);
    assert_return_value_equal("|%05c|", 'A');
    assert_return_value_equal("|%010c|", 'B');
    assert_return_value_equal("|%.5d|", 42);
    assert_return_value_equal("|%.10d|", 42);
    assert_return_value_equal("|%.3d|", 42);
    assert_return_value_equal("|%.5d|", -42);
    assert_return_value_equal("|%.10d|", -42);
    assert_return_value_equal("|%.0d|", 0);
    assert_return_value_equal("|%.0d|", 42);
    assert_return_value_equal("|%.5s|", "Hello World");
    assert_return_value_equal("|%.10s|", "Hello World");
    assert_return_value_equal("|%.0s|", "Hello World");
    assert_return_value_equal("|%.15s|", "Hello World");
    assert_return_value_equal("|%.8x|", 255);
    assert_return_value_equal("|%.8X|", 255);
    assert_return_value_equal("|%.0x|", 0);
    assert_return_value_equal("|%.0x|", 255);
    assert_return_value_equal("|%10.5d|", 42);
    assert_return_value_equal("|%20.10d|", 42);
    assert_return_value_equal("|%5.3d|", 42);
    assert_return_value_equal("|%10.5d|", -42);
    assert_return_value_equal("|%-10.5d|", 42);
    assert_return_value_equal("|%-10.5d|", -42);
    assert_return_value_equal("|%10.5s|", "Hello World");
    assert_return_value_equal("|%-10.5s|", "Hello World");
    assert_return_value_equal("|%20.10s|", "Hello World");
    assert_return_value_equal("|%5.3s|", "Hello World");
    assert_return_value_equal("|%#x|", 255);
    assert_return_value_equal("|%#X|", 255);
    assert_return_value_equal("|%#x|", 0);
    assert_return_value_equal("|%#X|", 0);
    assert_return_value_equal("|%#10x|", 255);
    assert_return_value_equal("|%#010x|", 255);
    assert_return_value_equal("|%+d|", 42);
    assert_return_value_equal("|%+d|", -42);
    assert_return_value_equal("|%+d|", 0);
    assert_return_value_equal("|%+5d|", 42);
    assert_return_value_equal("|%+05d|", 42);
    assert_return_value_equal("|%+10.5d|", 42);
    assert_return_value_equal("|% d|", 42);
    assert_return_value_equal("|% d|", -42);
    assert_return_value_equal("|% d|", 0);
    assert_return_value_equal("|% 5d|", 42);
    assert_return_value_equal("|% 05d|", 42);
    assert_return_value_equal("|% +d|", 42);
    assert_return_value_equal("|%p|", ptr1);
    assert_return_value_equal("|%p|", ptr2);
    assert_return_value_equal("|%20p|", ptr1);
    assert_return_value_equal("|%-20p|", ptr1);
    assert_return_value_equal("|%020p|", ptr1);
    assert_return_value_equal("|%p|", (void*)null_ptr);
    assert_return_value_equal("|%20p|", (void*)null_ptr);
    assert_return_value_equal("|%-20p|", (void*)null_ptr);
    assert_return_value_equal("|%*d|", 10, 42);
    assert_return_value_equal("|%*d|", -10, 42);
    assert_return_value_equal("|%*s|", 10, "Hello");
    assert_return_value_equal("|%*s|", -10, "Hello");
    assert_return_value_equal("|%.*d|", 5, 42);
    assert_return_value_equal("|%.*d|", -5, 42);
    assert_return_value_equal("|%.*s|", 5, "Hello World");
    assert_return_value_equal("|%.*s|", -5, "Hello World");
    assert_return_value_equal("|%*.*d|", 10, 5, 42);
    assert_return_value_equal("|%*.*d|", -10, 5, 42);
    assert_return_value_equal("|%*.*s|", 10, 5, "Hello World");
    assert_return_value_equal("|%*.*s|", -10, -5, "Hello World");
    assert_return_value_equal("|%-#+ 010.5d|", 42);
    assert_return_value_equal("|%-#+ 010.5d|", -42);
    assert_return_value_equal("|%-# 010.5x|", 255);
    assert_return_value_equal("|%-# 010.5X|", 255);
    assert_return_value_equal("|%+05d|", 42);
    assert_return_value_equal("|%+05d|", -42);
    assert_return_value_equal("|%-+10.5d|", 42);
    assert_return_value_equal("%d %s %x %c", 42, "test", 255, 'A');
    assert_return_value_equal("%d + %d = %d", 10, 20, 30);
    assert_return_value_equal("|%d| |%s| |%x| |%c|", 42, "hello", 255, 'Z');
    assert_return_value_equal("%d", INT_MAX);
    assert_return_value_equal("%d", INT_MIN);
    assert_return_value_equal("%u", UINT_MAX);
    assert_return_value_equal("%x", UINT_MAX);
    assert_return_value_equal("%X", UINT_MAX);
    assert_return_value_equal("%.0d", 0);
    assert_return_value_equal("%.0d", 42);
    assert_return_value_equal("%.0x", 0);
    assert_return_value_equal("%.0s", "Hello");
    assert_return_value_equal("%.0c", 'A');
    assert_return_value_equal("%0d", 42);
    assert_return_value_equal("%00d", 42);
    assert_return_value_equal("%0005d", 42);
    assert_return_value_equal("%-05d", 42);
    assert_return_value_equal("%%");
    assert_return_value_equal("%% %%");
    assert_return_value_equal("%%d", 42);
    assert_return_value_equal("%s", (char*)NULL);
    assert_return_value_equal("%10s", (char*)NULL);
    assert_return_value_equal("%-10s", (char*)NULL);
    assert_return_value_equal("%.5s", (char*)NULL);
    assert_return_value_equal("%d %s %x %c", 42, "hello", 255, 'A');
    assert_return_value_equal("%c %d %s %x", 'Z', 123, "world", 0xabc);
    assert_return_value_equal("%s %c %x %d", "test", 'B', 0xff, -42);
    assert_return_value_equal("%x %d %c %s", 0x123, -999, 'C', "foo");
    assert_return_value_equal("%p %d %s", &x, 42, "hello");
    assert_return_value_equal("%d %p %s", 123, &y, "world");
    assert_return_value_equal("%s %d %p", "test", 456, &z);
    assert_return_value_equal("%p %p %p", &x, &y, &z);
    assert_return_value_equal("%u %d %x", 4294967295u, -42, 255);
    assert_return_value_equal("%d %u %X", 123, 4294967295u, 0xABCDEF);
    assert_return_value_equal("%x %X %u", 0xabc, 0xDEF, 123456);
    assert_return_value_equal("|%5d|%10s|%3c|", 42, "hello", 'A');
    assert_return_value_equal("|%10d|%5s|%8c|", 123, "world", 'B');
    assert_return_value_equal("|%3d|%15s|%6c|", -42, "test", 'C');
    assert_return_value_equal("|%8d|%4s|%12c|", 0, "foo", 'D');
    assert_return_value_equal("|%-5d|%-10s|%-3c|", 42, "hello", 'A');
    assert_return_value_equal("|%-10d|%-5s|%-8c|", 123, "world", 'B');
    assert_return_value_equal("|%-3d|%-15s|%-6c|", -42, "test", 'C');
    assert_return_value_equal("|%05d|%010s|%03c|", 42, "hello", 'A');
    assert_return_value_equal("|%010d|%05s|%08c|", 123, "world", 'B');
    assert_return_value_equal("|%05d|%010x|%08X|", 42, 255, 255);
    assert_return_value_equal("|%.5d|%.3s|%.2c|", 42, "hello", 'A');
    assert_return_value_equal("|%.10d|%.5s|%.1c|", 123, "world", 'B');
    assert_return_value_equal("|%.3d|%.10s|%.0c|", -42, "test", 'C');
    assert_return_value_equal("|%.8d|%.4s|%.6c|", 0, "foobar", 'D');
    assert_return_value_equal("|%10.5d|%15.10s|%8.3c|", 42, "hello world", 'A');
    assert_return_value_equal("|%8.3d|%12.8s|%10.5c|", 123, "test string", 'B');
    assert_return_value_equal("|%15.10d|%10.5s|%12.8c|", -42, "foo bar", 'C');
    assert_return_value_equal("|%5.2d|%20.15s|%6.4c|", 0, "very long string", 'D');
    assert_return_value_equal("|%-10.5d|%-15.10s|%-8.3c|", 42, "hello world", 'A');
    assert_return_value_equal("|%-8.3d|%-12.8s|%-10.5c|", 123, "test string", 'B');
    assert_return_value_equal("|%-15.10d|%-10.5s|%-12.8c|", -42, "foo bar", 'C');
    assert_return_value_equal("%#x %#X %d", 255, 255, 42);
    assert_return_value_equal("%d %#x %#X", 123, 0xabc, 0xDEF);
    assert_return_value_equal("%#x %d %#X", 0, 42, 0);
    assert_return_value_equal("%#10x %#-10X %d", 255, 255, 42);
    assert_return_value_equal("%#010x %#-10X %d", 255, 255, 42);
    assert_return_value_equal("%+d % d %+d", 42, 42, -42);
    assert_return_value_equal("% d %+d % d", 123, -123, 456);
    assert_return_value_equal("%+5d % 5d %+10d", 42, 42, -42);
    assert_return_value_equal("%-+5d %- 5d %+d", 42, 42, -42);
    assert_return_value_equal("%+05d % 05d %+10.5d", 42, 42, -42);
    assert_return_value_equal("%+d %d % d %+d", 42, 123, 456, -42);
    assert_return_value_equal("% d %+d %d % d", 123, -123, 456, -456);
    assert_return_value_equal("%+d % d %+d % d", 1, 2, -3, -4);
    assert_return_value_equal("|%+010.5d|%-#15.10x|%-+10.5d|", 42, 255, 42);
    assert_return_value_equal("|%#010x|%+10.5d|%-#15.10X|", 255, -42, 255);
    assert_return_value_equal("|%-+10.5d|%#010x|%+10.5d|", 42, 0, -42);
    assert_return_value_equal("|%-#15.10x|%-+10.5d|%#010X|", 255, 42, 255);
    assert_return_value_equal("%*d %*d %*s", 5, 42, 10, 123, 8, "hello");
    assert_return_value_equal("%*d %*s %*c", 3, 42, 15, "world", 6, 'A');
    assert_return_value_equal("%*d %*d %*d", -5, 42, -10, 123, -8, 456);
    assert_return_value_equal("%.*d %.*s %.*c", 5, 42, 3, "hello", 2, 'A');
    assert_return_value_equal("%.*d %.*s %.*x", 10, 123, 5, "world", 8, 255);
    assert_return_value_equal("%.*d %.*s %.*X", -5, 42, -3, "hello", -8, 255);
    assert_return_value_equal("%*.*d %*.*s %*.*c", 10, 5, 42, 15, 10, "hello", 8, 3, 'A');
    assert_return_value_equal("%*.*d %*.*x %*.*X", 8, 3, 123, 12, 8, 255, 10, 5, 255);
    assert_return_value_equal("%-*.*d %-*.*s %-*.*c", 10, 5, 42, 15, 10, "world", 8, 3, 'B');
    assert_return_value_equal("%s %s %s", "hello", null_str, "world");
    assert_return_value_equal("%10s %-10s %.5s", null_str, null_str, null_str);
    assert_return_value_equal("%*.*s %-*.*s", 10, 5, null_str, 15, 10, null_str);
    assert_return_value_equal("%d %% %s %% %x", 42, "hello", 255);
    assert_return_value_equal("%% %d %% %s %% %x %%", 42, "world", 255);
    assert_return_value_equal("%d%%%s%%%x", 42, "test", 255);
    assert_return_value_equal("%% %+d %% %#x %% %c %%", 42, 255, 'A');
    assert_return_value_equal("%.0d %.0x %.0s %.0c", 0, 0, "hello", 'A');
    assert_return_value_equal("%.0d %.0x %.0s %.0c", 42, 255, "world", 'B');
    assert_return_value_equal("%0d %0x %0s %0c", 42, 255, "test", 'A');
    assert_return_value_equal("%00d %00x %00s %00c", 42, 255, "hello", 'B');
    assert_return_value_equal("%-020d %0-20x %0-20s %-020c", 42, 255, "world", 'A');
    assert_return_value_equal("%0-10.5d %-#010x %-20s %-5c", 42, 255, "test", 'B');
	assert_return_value_equal("%-05d %-#030p %-20s %-5c", 42, &a, "test", 'B');
	assert_return_value_equal(
        "%d %u %x %X %c %s %p",
        INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 'A', "test", (void*)0x12345
    );

    assert_return_value_equal(
        "%d %d %u %x %X",
        INT_MIN, INT_MAX, UINT_MAX, 0, 0
    );

    assert_return_value_equal(
        "%+d %+d % d % u %#x %#X",
        INT_MAX, INT_MIN, 42, 123, 255, 255
    );
	assert_return_value_equal(
        "%-+010.5d %#015x %+10.5d %#-10X %u %c %-20s %p %d",
        42, 255, -42, 255, 123, 'B', "test string", &x, 999
    );
	assert_return_value_equal(
        "%c %s %p %d %i %u %x %X %%",
        'A', "test", &x, 42, -42, 123, 255, 255
    );

    assert_return_value_equal(
        "%+d % d %#x %#X %u %c %s %p %%",
        42, 42, 255, 255, 123, 'B', "hello", &x
    );

    assert_return_value_equal(
        "%-10.5d %+10.5d %-#15.10x %#010X %-20.10s %p",
        42, -42, 255, 255, "world", &x
    );
	assert_return_value_equal(
        "%d %s %x %c %p %u %X %+d % d %#x",
        42, "test", 255, 'A', (void*)0x123, 123, 0xDEF, 456, 456, 255
    );
	assert_return_value_equal(
        "%d %d %d %d %d %d %d %d %d %d",
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    );

    assert_return_value_equal(
        "%s %s %s %s %s %s %s %s %s %s",
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"
    );

    assert_return_value_equal(
        "%c %c %c %c %c %c %c %c %c %c",
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
    );

    assert_return_value_equal(
        "%x %x %x %x %x %X %X %X %X %X",
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    );
	assert_return_value_equal(
        "%d %s %x %c %d %s %x %c %d %s %x %c %d %s %x %c",
        1, "one", 0x1, 'A', 2, "two", 0x2, 'B', 3, "three", 0x3, 'C', 4, "four", 0x4, 'D'
    );
	assert_return_value_equal(
        "%+d % d %#x %#X %u %c %s %p %+d % d %#x %#X",
        1, 1, 1, 1, 1, 'A', "one", (void*)0x1, 2, 2, 2, 2
    );
	assert_return_value_equal(
        "Formatted: %+10.5d, Hex: %-#15.10x, Upper: %#010X, "
        "Unsigned: %u, Char: %c, String: %-20.10s, Pointer: %p, "
        "Percent: %%, Another: %d, Hex2: %#x",
        42, 255, 255, 123, 'A', "hello world", (void*)0x12345, -42, 0xABC
    );
	assert_return_value_equal(
        "|%-10.5d|%+10.5d|%-#15.10x|%#010X|%+d|% d|%u|%c|%-20.10s|%p|",
        42, -42, 255, 255, 123, 123, 456, 'C', "mixed types", (void*)0xABCD
    );
	assert_return_value_equal(
        "%#-20d % 10.5s %-0#25.4x %c %p %u %X %+21.10d % d %#x",
        42, "test", 255, 'A', &x, 123, 0xDEF, 456, 456, 255
    );
    assert_return_value_equal(
        "%d %s %x %c %p %u %X %+d % d %#x",
        -42, "another", 0xabc, 'Z', &y, 456, 0x123, -123, -123, 0
    );
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
