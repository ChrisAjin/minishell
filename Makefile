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