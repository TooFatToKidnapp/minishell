/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:31:44 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:45:16 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"

int	part3(t_args *args, t_env *env)
{
	if (ft_strcmp(args->cmd[0], "pwd") == 0)
		return (pwd(), 1);
	else if (ft_strcmp(args->cmd[0], "echo") == 0)
		return (echo(args->cmd), 1);
	else if (ft_strcmp(args->cmd[0], "env") == 0)
		return (print_env(env), 1);
	else if (ft_strcmp(args->cmd[0], "export") == 0)
	{
		if (args->cmd[1] == NULL)
			sort_and_print_env(env);
		return (1);
	}
	else if (!ft_strcmp(args->cmd[0], "unset")
		|| !ft_strcmp(args->cmd[0], "exit")
		|| !ft_strcmp(args->cmd[0], "cd")
		|| !ft_strcmp(args->cmd[0], "/usr/bin/cd"))
		return (1);
	return (0);
}

int	builtins_check(t_args *args, t_env **env, t_all *vars)
{
	if (lst_size(vars->node) == 1)
	{
		if (ft_strcmp(args->cmd[0], "cd") == 0
			|| ft_strcmp(args->cmd[0], "/usr/bin/cd") == 0)
			cd(vars->node->arg, *env);
		else if (ft_strcmp(args->cmd[0], "pwd") == 0)
			pwd();
		else if (ft_strcmp(args->cmd[0], "echo") == 0)
			echo(args->cmd);
		else if (ft_strcmp(args->cmd[0], "env") == 0)
			print_env(*env);
		else if (ft_strcmp(args->cmd[0], "export") == 0)
			export(env, args->cmd, vars->built_envp);
		else if (ft_strcmp(args->cmd[0], "unset") == 0)
			unset(env, args->cmd);
		else if (ft_strcmp(args->cmd[0], "exit") == 0)
			exit_shell(args->cmd, 0);
		return (1);
	}
	else
		if (part3(args, *env) == 1)
			return (1);
	return (0);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
