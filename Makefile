CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = include/
LIB = -L libft/ -lft
NAME = minitest

SRC = main_test.c builtins/builtins_utils.c builtins/echo.c builtins/cd.c builtins/pwd.c builtins/exit.c builtins/env.c

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
	mkdir -p obj/builtins

clean:
	make fclean -C libft/
	rm -rf $(OBJ_PATH)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re