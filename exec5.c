/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:25:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:44:12 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtins(t_args *args, int index, t_all *vars, t_env **env)
{
	int		fd_in;
	int		fd_out;
	int		tmp_in;
	int		tmp_out;

	fd_in = dup(0);
	fd_out = dup(1);
	tmp_in = dup(0);
	tmp_out = dup(1);
	if (ft_here_doc(args, &fd_in)
		|| ft_if_infile(args, index, &fd_in, vars)
		|| ft_if_outfile(args, index, &fd_out, vars))
		return ;
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	builtins_check(args, env, vars);
	dup2(tmp_out, 1);
	dup2(tmp_in, 0);
	close(tmp_in);
	close(tmp_out);
	close(fd_in);
	close(fd_out);
	vars->i--;
	var.exit_code = 0;
}

void	check_mini(t_all *vars, char **envp)
{
	if (!ft_strcmp(vars->cmd_path, "minishell")
		|| !ft_strcmp(vars->cmd_path, "MINISHELL"))
	{
		free_2d(envp);
		exit(1);
	}
}

void	*exec_cmd(t_args *args, int index, t_env *env, t_all *vars)
{
	int		fd_in;
	int		fd_out;
	char	**envp;

	vars->paths = ft_findpath(env);
	ft_path_checker(vars->paths);
	fd_in = dup(0);
	fd_out = dup(1);
	if (ft_here_doc(args, &fd_in)
		|| ft_if_infile(args, index, &fd_in, vars)
		|| ft_if_outfile(args, index, &fd_out, vars))
		exit(1);
	vars->cmd_path = ft_path(vars->paths, args->cmd[0]);
	ft_path_null(vars->cmd_path);
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	envp = create_env(env);
	if (envp == NULL)
		return (perror("Error\n"), exit(1), NULL);
	close_all(vars, fd_in, fd_out);
	check_mini(vars, envp);
	if (execve(vars->cmd_path, args->cmd, envp) == -1)
		perror("Error");
	return (free_2d(envp), exit(1), NULL);
}

void	free_empty(t_lists **list)
{
	t_lists	*head;

	head = *list;
	while (head)
	{
		if ((head)->value[0] == '\0')
		{
			free_block(list, "\0");
			head = *list;
		}
		else
			(head) = (head)->next;
	}
}

int	int_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
		if (!s[i++])
			return (1);
	return (0);
}
