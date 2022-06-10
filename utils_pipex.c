/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:55 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/09 19:08:51 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_routine(t_all *vars, t_args *commands, t_env *env)
{
	vars->i = 0;
	while (vars->i < vars->fork_num)
	{
		vars->pid[vars->i] = fork();
		var.forks++;
		if (vars->pid[vars->i] == -1)
		{
			printf("ERROR\n");
			exit(1);
		}
		if (vars->pid[vars->i] == 0)
		{
			unlink("tmp");
			exec_cmd(vars, commands, env, vars->i);
			exit(1);
		}
		(vars->i)++;
	}
}

char	*ft_findpath(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_findpath_char(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	ft_malloc(void *tab)
{
	if (tab == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
}

char	*ft_strjoin_pipex(char const *s1, char const *s2)
{
	size_t	len;
	char	*s3;

	if (!s1)
		return ((char *)s2);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(sizeof(char) * len);
	if (s3 == 0)
		return (0);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcat(s3, s2, len);
	return (s3);
}
