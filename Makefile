INCLUDE = minishell.h

SRC =	minishell.c\
		pwd.c\
		parsing.c\
		pipes.c\
		quotes.c\
		directions.c\
		parsing_util.c\
		free.c\
		exit.c\
		unset.c\
		unset_util.c\
		env.c\
		cd.c\
		ft_dollar.c\
		ft_dollar2.c\
		echo.c\
		export.c\
		export_util.c\
		export_util2.c\
		pipex_dub.c\
		utils_pipex2.c\
		utils_pipex3.c\
		utils_pipex.c\
		ft_execve_error.c\
		cmd_cases.c\
		parsing_exec.c\
		parsing_exec2.c\
		GNL/get_next_line.c\
		GNL/get_next_line_utils.c\

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

rl_FLAGS = -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include

OBJ = $(SRC:%.c=%.o)

NAME = minishell

all : ft_libft $(NAME)

%.o : %.c $(INCLUDE)
		$(CC) $(FLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) -fsanitize=address $(FLAGS) $(OBJ) libft/libft.a -L  $(shell brew --prefix readline)/lib -lreadline -o $(NAME)

ft_libft :
		@make -C libft

clean :
	rm -f $(OBJ) && make -C libft clean

fclean : clean
	rm -f minishell && make -C libft fclean

re : fclean all
# -fsanitize=address
