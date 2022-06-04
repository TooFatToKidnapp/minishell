/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:00:43 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/02 18:31:06 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd( '\n', 1);
		rl_on_new_line(); // output pormpt on a new line
		rl_replace_line("", 0); // print the given text after the prompt
		rl_redisplay(); //display the changes mentioned above
	}
}

char	*get_prompt() //returns the prompt
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*pwd;

	s1 = ft_strdup("\e[1;33mMinishell:\e[0;37m");
	s2 = ft_strdup("\e[1;34m");
	pwd = get_pwd();
	s3 = ft_strjoin(s2,pwd);
	free(pwd);
	free(s2);
	s2 = ft_strjoin(s3,"$ \e[0;37m");
	free(s3);
	s3 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s3);
}

void	init_shell(t_env *env, char **envp)
{
	char	*str;
	t_node	**node;

	while (true)
	{
		str = get_prompt();
		var.user_input = readline(str);
		free(str);
		if (var.user_input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break;;
		}
		if (var.user_input != NULL)
			add_history(var.user_input);
		node = parser(node);
		if (node != NULL)
		{
			if (ft_strcmp((*node)->arg[0] , "cd") == 0 || ft_strcmp((*node)->arg[0] , "/usr/bin/cd") == 0)
				cd((*node)->arg, env);
			else if (ft_strcmp((*node)->arg[0] , "pwd") == 0)
				pwd();
			else if (ft_strcmp((*node)->arg[0] , "echo") == 0)
				echo((*node)->arg);
			else if (ft_strcmp((*node)->arg[0] , "env") == 0)
				print_env(env);
			else if (ft_strcmp((*node)->arg[0] , "export") == 0)
				export(env, (*node)->arg, envp);
		}
		if(!ft_strcmp(var.user_input, "exit"))
		{
			if (node != NULL)
				free_list(node);
			free(var.user_input);
			exit(0);
		}
		free(var.user_input);
		if (node != NULL)
			free_list(node);
	}
	free(var.user_input);
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;
	(void)av;
	(void)ac;
	rl_catch_signals = 0;
	var.exit_code = 0;
	signal(SIGINT, sigint);  // ctr+c
	signal(SIGQUIT, SIG_IGN);  /* ctr+\ */
	signal(SIGTSTP, SIG_IGN); // ctr + z
	env = get_env(envp);
	init_shell(env, envp);
	free_env(env);
	return (0);
}
