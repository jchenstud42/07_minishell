# Program name
NAME		=	minishell

# Compilation flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
READLINE_FLAG = -lreadline

# Libft
LIBFT_PATH	=	src/libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./src/libft/\
				-I ./inc/

# Sources
SRC_PATH	=	src/
SRC			=	minishell.c \
				error_handler.c \
				test.c \
				initialization.c \
				token/init_token_list.c \
				token/tokenize_line.c \
				token/token_utils.c \
				parsing/check_line.c \
				parsing/is_special_token.c \
				free/free.c \
				exec/exec.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/pwd.c \
				builtins/unset.c

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	=	obj/
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

# Color codes for terminal output
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SILENT		=	> /dev/null 2>&1

# --------------------------------------------------------------------------------- #


# Default target calling for the executable
all: $(LIBFT) $(NAME)

# Target for making the Libft
$(LIBFT):
	@echo "$(GREEN)Making $(LIBFT)..."
	@make -sC $(LIBFT_PATH)

# Target to build the mandatory part
$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) $(READLINE_FLAG)
	@echo "$(YELLOW)\n\o\ Compilation completed! /o/\n"

# Compiles C source files into object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Cleans object files and dependencies
clean:
	@echo "$(GRAY)Removing .o object files..."
	@rm -rf $(OBJ_PATH) $(SILENT)
	@make clean -C $(LIBFT_PATH) $(SILENT)
	@echo "$(GRAY).o object files removed!"

# Cleans everything generated by the Makefile
fclean:	clean
	@echo "$(GRAY)Removing $(NAME)..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "$(YELLOW)\n\o\ All created files have been removed! /o/\n"

# Cleans everything generated by the Makefile and rebuilds all
re: fclean all

# Phony targets
.PHONY: all clean fclean re
