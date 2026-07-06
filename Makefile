CC = cc
CFLAGS += -Wall -Wextra -Werror -I .

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -I/usr/local/include
LDFLAGS = -L/usr/local/lib
GTEST_LIBS = -lgtest -lgtest_main -lpthread

LIBFT_DIR = libft
OBJ_DIR = build
VPATH = $(LIBFT_DIR):.
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c  \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c  \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c  \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_lstadd_front.c \
		ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstsize.c ft_lstnew.c \
		ft_substr.c ft_strtrim.c ft_strmapi.c ft_strjoin.c \
		ft_striteri.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_itoa.c \
		ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_itoa_u_base.c \
		ft_printf.c ft_printers_csidu.c ft_printers_xXp.c ft_parsers.c

NAME = libftprintf.a

TEST_NAME = test_ft_printf
TEST_SRC = test_ft_printf.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

bonus: all
	@echo "$(GREEN)Bonus done"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Created folder: $(OBJ_DIR)$(NC)"

$(NAME): $(OBJECTS)
	@echo "$(BLUE)Creating library...$(NC)"
	@ar rcs $@ $^
	@echo "$(GREEN)Library created: $(NAME)$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling object file $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME) $(TEST_OBJ)
	@echo "$(BLUE)Building tests...$(NC)"
	$(CXX) $(CXXFLAGS) -o $(TEST_NAME) $(TEST_OBJ) $(NAME) $(LDFLAGS) $(GTEST_LIBS)
	@echo "$(GREEN)✓ Tests built: $(TEST_NAME)$(NC)"
	@echo "$(BLUE)Running tests...$(NC)"
	@./$(TEST_NAME)
	@echo "$(GREEN)✓ Tests complete$(NC)"

$(TEST_OBJ): $(TEST_SRC)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning...$(NC)"
	@rm -rf $(OBJ_DIR) $(TEST_OBJ)
	@echo "$(GREEN)✓ Cleaned object files$(NC)"

fclean: clean
	@echo "$(YELLOW)Full cleaning...$(NC)"
	@rm -f $(NAME) $(TEST_NAME)
	@echo "$(GREEN)✓ Cleaned all$(NC)"

re: fclean all

.PHONY: all clean fclean re bonus test
