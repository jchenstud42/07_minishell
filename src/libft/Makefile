# Program Name
NAME		=	libft.a

# Compiler
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

# Libft
LIBC		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
				ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
				ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
				ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c

ADD			=	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c	\
				ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

STRUCT		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

PRINTF		=	ft_printf.c ft_printchar.c ft_printstr.c ft_printnbr.c ft_printunsigned.c \
				ft_printhex.c ft_printptr.c

GNL			=	get_next_line.c get_next_line_fds.c get_next_line_utils.c

AUTRE		=	ft_strcmp.c ft_strstr.c ft_chardup.c

# Includes
INC			=	-I .

# Sources
SRC_PATH	=	./
SRC			=	$(LIBC) $(ADD) $(STRUCT) $(PRINTF) $(GNL) $(AUTRE)
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	=	obj/
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))


# ------------------------------------------------------------------ #


all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "Compiling Libft..."
	@ar rcs $(NAME) $(OBJS)
#ar : permet de creer une archive (.a) qui va regrouper tous les .o pour creer une bibliotheque statique


clean:
	@echo "Removing .o object files from Libft..."
	@rm -rf $(OBJ_PATH)

fclean:	clean
	@echo "Removing Libft..."
	@rm -f $(NAME)"

re: fclean all

.PHONY: all clean fclean re
