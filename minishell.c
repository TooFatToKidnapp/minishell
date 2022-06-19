/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:00:43 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/19 14:52:11 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit(int sig)
{
	if (sig == SIGQUIT && var.forks > 0)
	{
		if (var.forks == 1
			&& ft_strcmp(var.user_input, "./minishell") != 0)
		{
			printf("QUIT: 3\n");
			var.exit_code = 131;
		}
		else if (ft_strcmp(var.user_input, "./minishell") != 0)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		if (var.forks == 0)
		{
			var.ctrl_c = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			var.exit_code = 1;
		}
		else
		{
			if (ft_strcmp(var.user_input, "./minishell") != 0)
				printf("\n");
			rl_redisplay();
			var.exit_code = 1;
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
		node = parser(node);
		if (node != NULL)
			exec(*node, &env, envp);
		free(var.user_input);
		if (node != NULL)
			free_list(node);
	}
	free(var.user_input);
}

/*	﷽	*/
int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	(void)ac;
	rl_catch_signals = 0;
	var.exit_code = 0;
	var.ctrl_c = 0;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	signal(SIGTSTP, SIG_IGN);
	env = get_env(envp, 0);
	init_shell(env, envp);
	free_all_env(env);
	return (0);
}
