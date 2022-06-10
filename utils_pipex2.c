/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:42:43 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/07 21:39:00 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init(t_all *var, t_env *env, int ac)
{
	var->paths = ft_findpath(env);
	ft_path_checker(var->paths);
	var->fork_num = ac;
	var->pipe_num = var->fork_num - 1;
	var->i = 0;
	var->j = 0;
}

void	ft_init2(t_all *var)
{
	var->p = (int **)malloc(sizeof(int *) * var->pipe_num);
	ft_malloc(var->p);
	var->pid = (pid_t *)malloc(sizeof(pid_t) * var->fork_num);
	ft_malloc(var->pid);
	while (var->i < var->pipe_num)
	{
		var->p[var->i] = (int *)malloc(sizeof(int) * 2);
		if (var->p[var->i] == NULL)
		{
			printf("ERROR\n");
			exit(1);
		}
		if (pipe(var->p[var->i]) == -1)
		{
			printf("ERROR\n");
			exit(1);
		}
		(var->i)++;
	}
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

void	ft_file(int fd, char *path, char **cmd)
{
	if (fd < 0)
	{
		free(path);
		free_memory_pipex(cmd);
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
}

void	ft_read(int *p, char *path, char **cmd)
{
	char	*str;

	str = malloc(2);
	read(p[0], str, 2);
	if (ft_strncmp(str, "-1", 2) == 0)
	{
		free(path);
		free_memory_pipex(cmd);
		close(p[1]);
		close(p[0]);
		free(str);
		exit(1);
	}
	free(str);
}
