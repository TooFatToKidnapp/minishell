/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/09 18:47:33 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	lst_size(t_node *node)
{
	int	ac;

	ac = 0;
	while (node)
	{
		ac++;
		node = node->next;
	}
	return (ac);
}

char	*ft_path(char *env, char *av)
{
	char	**path;
	char	*check;
	char	*try;
	int		a;

	a = 0;
	try = NULL;
	if (access(av, F_OK) == 0)
		return (ft_strdup(av));
	path = ft_split(env + 5, ':');
	check = ft_strjoin_pipex("/", av);
	while (path[a])
	{
		try = ft_strjoin_pipex(path[a], check);
		if (access(try, F_OK) == 0)
			return (free_memory_pipex(path),
				free(check), try);
		a++;
		free(try);
	}
	free_memory_pipex(path);
	free(check);
	return (NULL);
}

char	**create_env(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**envp;

	i = 0;
	tmp = env;
	while (env)
	{
		env = env->next;
		i++;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (envp == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	envp[i] = NULL;
	env = tmp;
	create_env2(env, envp);
	return (envp);
}

void	exec_cmd(t_all *var, t_args *commandes, t_env *env, int index)
{
	char	**envp;
	int		fd_in;
	int		fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	var->cmd_path = ft_path(var->paths, commandes[index].cmd[0]);
	ft_path_null(var->cmd_path);
	ft_here_doc(commandes, index, &fd_in);
	ft_if_infile(commandes, index, &fd_in, var);
	ft_if_outfile(commandes, index, &fd_out, var);
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	close_all(var, fd_in, fd_out);
	envp = create_env(env);
	if (envp == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	execve(var->cmd_path, commandes[index].cmd, envp);
}

void	pipex(t_node *node, t_env *env)
{
	t_args	*commands;

	commands = parse_arg(node);
	normal_mode(commands, env, node);
	free_commands(commands, lst_size(node));
}
