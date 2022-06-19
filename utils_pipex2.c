/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:42:43 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/18 17:58:53 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_init(t_all *var, t_node *node, char **envp)
{
	var->fork_num = lst_size(node);
	var->pipe_num = var->fork_num - 1;
	var->i = 0;
	var->j = 0;
	var->node = node;
	var->built_envp = envp;
	return (0);
}

int	ft_init2(t_all *var)
{
	var->p = (int **)malloc(sizeof(int *) * var->pipe_num);
	ft_malloc(var->p);
	while (var->i < var->pipe_num)
	{
		var->p[var->i] = (int *)malloc(sizeof(int) * 2);
		if (var->p[var->i] == NULL)
		{
			printf("ERROR2\n");
			exit(1);
		}
		if (pipe(var->p[var->i]) == -1)
		{
			printf("ERROR1\n");
			return (1);
		}
		(var->i)++;
	}
	return (0);
}

void	free_memory_pipex(char **s)
{
	int	block;

	block = 0;
	while (s[block])
	{
		free(s[block]);
		block++;
	}
	free(s);
}

void	ft_path_checker(char *paths)
{
	if (paths == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(1);
	}
}

void	ft_close_free(t_all *vars, char **input)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while (i < vars->i)
	{
		waitpid(-1, &state, 0);
		if (WIFEXITED(state) && WEXITSTATUS(state) == 1)
			var.exit_code = 127;
		var.forks--;
		i++;
	}
	unlink("tmp");
	free_2d(input);
	vars->j = 0;
	while (vars->j < vars->pipe_num)
	{
		close(vars->p[vars->j][0]);
		close(vars->p[vars->j][1]);
		(vars->j)++;
	}
	free_var(vars);
}
