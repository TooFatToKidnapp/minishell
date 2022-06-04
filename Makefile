INCLUDE = minishell.h

SRC =	minishell.c\
		pwd.c\
		parsing.c\
		pipes.c\
		quotes.c\
		directions.c\
		util.c\
		free.c\
		env.c\
		cd.c\
		echo.c\
		export.c\
		export_util.c\
		export_util2.c\

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

rl_FLAGS = -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include

OBJ = $(SRC:%.c=%.o)

NAME = minishell

all : ft_libft $(NAME)

%.o : %.c $(INCLUDE)
		$(CC) $(FLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) libft/libft.a $(OBJ) -L  $(shell brew --prefix readline)/lib -lreadline -ggdb3 -o $(NAME)

ft_libft :
		@make -C libft

clean :
	rm -f *.o && make -C libft clean

fclean : clean
	rm -f minishell && make -C libft fclean

re : fclean all
