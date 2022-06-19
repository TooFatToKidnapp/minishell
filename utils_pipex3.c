/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:25:05 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/18 18:05:04 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_var(t_all *var)
{
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

void	create_env2(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (env)
	{
		envp[i] = ft_strdup(env->name);
		envp[i] = ft_strjoin_gnl(envp[i], "=");
		envp[i] = ft_strjoin_gnl(envp[i], env->value);
		env = env->next;
		i++;
	}
}

int	check_if(t_all *vars, t_node *node, char **envp)
{
	if (ft_init(vars, node, envp) == 1)
		return (1);
	if (ft_init2(vars) == 1)
		return (1);
	return (0);
}
