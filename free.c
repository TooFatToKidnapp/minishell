/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:14:55 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/25 15:59:01 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2D(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_node **node)
{
	t_node	*next;
	t_node	*tmp;

	if ((*node) == NULL)
		return (free(node));
	next = (*node)->next;
	free_2D((*node)->arg);
	free((*node));
	while (next)
	{
		tmp = next;
		next = next->next;
		free_2D(tmp->arg);
		free(tmp);
	}
	free(node);
}

void	free_env(t_env *env)
{
	t_env	*next;
	t_env	*tmp;

	if (env == NULL)
		return ;
	next = env->next;
	free(env->value);
	free(env->name);
	free(env);
	while (next)
	{
		tmp = next;
		next = next->next;
		free(tmp->value);
		free(tmp->name);
		free(tmp);
	}
}
