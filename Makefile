<<<<<<< HEAD
NAME	=	minishell

CC		=	cc
FLAG	=	-Wall -Wextra -Werror -g3

DIRLIB	=	./Libft/
FILELIB	=	libft.a
NAMELFT	=	$(addprefix $(DIRLIB), $(FILELIB))

SRC_DIR	=	source/
OBJ_DIR	=	obj/
INCLUDE	=	-I ./include -I ./Libft
HEADER 	=	include/minishell.h

# Color

DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# Source
FILES	=	main tools_list free utils

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

# Add the path to the builtin folder to vpath
vpath %.c $(SRC_DIR) $(SRC_DIR)Tools 

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(DIRLIB)
	$(CC) $(FLAG) $(OBJS) $(NAMELFT) -lreadline $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)Minishell Compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : %.c $(HEADER) Makefile | $(OBJF)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

clean :
	@ make clean -sC $(DIRLIB)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@echo "$(MAGENTA)Minishell objects cleaned !$(DEF_COLOR)"

fclean : clean
	@ make clean -sC $(DIRLIB)
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)
	@echo "$(YELLOW)Minishell cleaned !$(DEF_COLOR)"

re : fclean all
	@echo "$(GREEN)Cleaned and rebuilt !$(DEF_COLOR)"

.PHONY : all clean fclean re
=======
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = include/
LIB = -L libft/ -lft
NAME = minitest

SRC = main.c builtins_utils.c echo.c cd.c

OBJS_BASE = $(SRC:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_BASE))

all: $(OBJ_PATH) $(NAME)

$(NAME) : $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $(NAME) $(OBJS) $(LIB) -lreadline

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@ 

$(OBJ_PATH):
	mkdir -p obj/

clean:
	make fclean -C libft/
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
>>>>>>> 39a52ab (brouillon cd/echo/exit/main)
