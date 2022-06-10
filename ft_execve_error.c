/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:11:52 by haitam            #+#    #+#             */
/*   Updated: 2022/06/09 19:05:27 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_split_check(char **cmd)
{
	if (*cmd == NULL)
	{
		perror("error");
		exit(0);
	}
}

void	ft_path_null(char *path)
{
	if (path == NULL)
	{
		ft_putstr_fd("Command not found\n", 1);
		exit(1);
	}
}

void	ft_execve_error(char *path, char **cmd, int a)
{
	free(path);
	(void)cmd;
	perror("execve error");
	if (a == 2)
		write(1, "-1", 2);
	exit(1);
}

void	ft_path_checker(char *paths)
{
	if (paths == NULL)
	{
		ft_putstr_fd("env error", 1);
		exit(1);
	}
}

void	ft_pid(pid_t pid, char *path, char **cmd)
{
	if (pid == -1)
	{
		free(path);
		free_memory_pipex(cmd);
		ft_putstr_fd("fork error", 1);
		exit(1);
	}
}
