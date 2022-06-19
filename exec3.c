/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:39:54 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/18 14:42:36 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_myargs(t_args **args)
{
	int	i;

	i = 0;
	free((*args)->in_file);
	free((*args)->out_file);
	free((*args)->out_append);
	free((*args)->limiter);
	if ((*args)->cmd != NULL)
	{
		while ((*args)->cmd[i])
		{
			free((*args)->cmd[i]);
			i++;
		}
		free((*args)->cmd);
	}
	free((*args));
}

void	if_cond(t_lists	*tmp1, t_lists	*tmp2, t_lists **list)
{
	if (tmp1 == NULL && tmp2)
	{
		(*list) = tmp2;
		(*list)->prev = NULL;
	}
	else if (!tmp2 && tmp1)
	{
		tmp1->next = NULL;
		(*list) = tmp1;
	}
	if (tmp1 && tmp2)
	{
		tmp1->next = tmp2;
		tmp2->prev = tmp1;
		(*list) = tmp1;
	}
}

void	free_block(t_lists **list, char *str)
{
	t_lists	*tmp1;
	t_lists	*tmp2;

	while ((*list))
	{
		if (!ft_strcmp((*list)->value, str))
			break ;
		(*list) = (*list)->next;
	}
	tmp2 = (*list)->next;
	tmp1 = (*list)->prev;
	free((*list)->value);
	free((*list));
	*list = NULL;
	if_cond(tmp1, tmp2, list);
	if (*list != NULL)
	{
		while ((*list)->prev != NULL)
			*list = (*list)->prev;
	}
}

int	mylist_size(t_lists *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_args	*list_cmd(t_lists *list, t_args *argum)
{
	int	i;

	i = 0;
	argum->cmd = (char **)malloc(sizeof(char *) * mylist_size(list) + 1);
	if (argum->cmd == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	argum->cmd[mylist_size(list)] = NULL;
	while (list)
	{
		argum->cmd[i] = ft_strdup((list)->value);
		i++;
		list = (list)->next;
	}
	return (argum);
}
