/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:00:43 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/12 19:08:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		var.exit_code = 1;
	}
	if (sig == SIGQUIT)
	{
		if (var.forks > 0)
		{
			if (var.forks == 1)
			{
				printf("QUIT: 3\n");
				var.exit_code = 131;
			}
			else
			{
				rl_on_new_line();
				rl_redisplay();
			}
		}
	}
}

char	*get_prompt(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*pwd;

	s1 = ft_strdup("\e[1;33mMinishell:\e[0;37m");
	s2 = ft_strdup("\e[1;34m");
	pwd = get_pwd();
	s3 = ft_strjoin(s2, pwd);
	free(pwd);
	free(s2);
	s2 = ft_strjoin(s3, "$ \e[0;37m");
	free(s3);
	s3 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s3);
}

void	ft_continue(t_node **node, t_env **env, char **envp)
{
	if (ft_strcmp((*node)->arg[0], "cd") == 0
		|| ft_strcmp((*node)->arg[0], "/usr/bin/cd") == 0)
		cd((*node)->arg, *env);
	else if (ft_strcmp((*node)->arg[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp((*node)->arg[0], "echo") == 0)
		echo((*node)->arg);
	else if (ft_strcmp((*node)->arg[0], "env") == 0)
		print_env(*env);
	else if (ft_strcmp((*node)->arg[0], "export") == 0)
		export(env, (*node)->arg, envp);
	else if (ft_strcmp((*node)->arg[0], "unset") == 0)
		unset(env, (*node)->arg, envp);
	else if (ft_strcmp((*node)->arg[0], "exit") == 0)
		exit_shell((*node)->arg, 0);
	else
		pipex(*node, *env);
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
			break ;
		}
		if (var.user_input != NULL)
			add_history(var.user_input);
		node = parser(node, env);
		if (node != NULL)
			ft_continue(node, &env, envp);
		free(var.user_input);
		if (node != NULL)
			free_list(node);
	}
	free(var.user_input);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	(void)ac;
	rl_catch_signals = 0;
	var.exit_code = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigint);
	signal(SIGTSTP, SIG_IGN);
	env = get_env(envp , 0);
	init_shell(env, envp);
	// free_env(env);
	return (0);
}
