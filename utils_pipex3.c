/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:25:05 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/09 19:08:41 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_var(t_all *var)
{
	free(var->pid);
	var->j = 0;
	while (var->j < var->pipe_num)
	{
		free(var->p[var->j]);
		var->j++;
	}
	free(var->p);
}

int	ft_limiter(char *line, char *limiter, int size)
{
	char	*limi_new;
	int		ret;

	limi_new = ft_strjoin(limiter, "\n");
	ret = ft_strncmp(line, limi_new, size);
	free(limi_new);
	return (ret);
}

void	free_commands(t_args *commands, int size)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < size)
	{
		free_inside(commands[i]);
		j = 0;
		while (commands[i].cmd[j] != NULL)
		{
			free(commands[i].cmd[j]);
			j++;
		}
		free(commands[i].cmd);
		i++;
	}
	free(commands);
}

void	normal_mode(t_args *commands, t_env *env, t_node *node)
{
	t_all	vars;

	ft_init(&vars, env, lst_size(node));
	ft_init2(&vars);
	ft_routine(&vars, commands, env);
	vars.j = 0;
	while (vars.j < vars.pipe_num)
	{
		close(vars.p[vars.j][0]);
		close(vars.p[vars.j][1]);
		(vars.j)++;
	}
	vars.i = 0;
	while (vars.i < vars.fork_num)
	{
		wait(NULL);
		var.forks--;
		(vars.i)++;
	}
	free_var(&vars);
}

void	create_env2(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (env)
	{
		envp[i] = ft_strdup(env->name);
		ft_malloc(envp[i]);
		envp[i] = ft_strjoin_pipex(envp[i], "=");
		ft_malloc(envp[i]);
		envp[i] = ft_strjoin_pipex(envp[i], env->value);
		ft_malloc(envp[i]);
		env = env->next;
		i++;
	}
}
