/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:00:43 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/21 19:44:30 by aabdou           ###   ########.fr       */
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

	s1 = ft_strdup("\e[1;33mMinishell:\e[0;37m");
	s2 = ft_strdup("\e[1;34m");
	s3 = ft_strjoin(s2,get_pwd());
	s2 = ft_strjoin(s3,"$ \e[0;37m");
	s3 = ft_strjoin(s1, s2);
	free(s2);
	return (s3);
}

void	init_shell()
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
		node = NULL;
		node = parser(node);
		if(!ft_strcmp(var.user_input, "exit"))
		{
			if (node != NULL)
				free_list(node);
			free(var.user_input);
			exit(0);
		}
		if (node != NULL)
			free_list(node);
	}
		free(var.user_input);

}

int main(int ac, char **av, char **envp)
{
	//t_env	*env;
	(void)envp;
	(void)av;
	(void)ac;
	rl_catch_signals = 0;
	var.exit_code = 0;
	//int i = 0;
	// while(envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	signal(SIGINT, sigint);  // ctr+c
	signal(SIGQUIT, SIG_IGN);  /* ctr+\ */
	signal(SIGTSTP, SIG_IGN); // ctr + z
	//env = fill_env(env);
	init_shell();
	return (0);
}
