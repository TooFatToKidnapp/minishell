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
		echo.c\
		export.c\
		export_util.c\
		export_util2.c\
		exec.c\
		exec2.c\
		exec3.c\
		exec4.c\
		exec5.c\
		exec6.c\
		utils_pipex2.c\
		utils_pipex3.c\
		utils_pipex4.c\
		utils_pipex.c\
		cmd_cases.c\
		parsing_exec.c\
		lexer.c\
		lexer_utils.c\
		lexer_utils2.c\
		token.c\
		GNL/get_next_line.c\
		GNL/get_next_line_utils.c\

CC = cc

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:%.c=%.o)

NAME = minishell

all : ft_libft $(NAME)

%.o : %.c $(INCLUDE)
		$(CC) $(FLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) libft/libft.a -L  $(shell brew --prefix readline)/lib -lreadline -o $(NAME)

ft_libft :
		@make -C libft

clean :
	rm -f $(OBJ) && make -C libft clean

fclean : clean
	rm -f minishell && make -C libft fclean

re : fclean all
