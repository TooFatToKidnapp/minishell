/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:37:01 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 15:14:39 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	add_back(t_lists **head, t_lists *new)
{
	t_lists	*tmp;

	tmp = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

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
	if (av == NULL || av[0] == '\0')
		return (printf("command not found\n"), exit(1), NULL);
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

void	free_mylist(t_lists **list)
{
	t_lists	*tmp;

	if (*list != NULL)
	{
		while ((*list)->next)
		{
			tmp = (*list);
			(*list) = (*list)->next;
			free(tmp->value);
			free(tmp);
			tmp = NULL;
		}
		free((*list)->value);
		free((*list));
		(*list) = NULL;
	}
}
