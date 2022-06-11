/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:14:55 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/11 13:49:10 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);;
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
	free_2d((*node)->arg);
	free((*node));
	while (next)
	{
		tmp = next;
		next = next->next;
		free_2d(tmp->arg);
		free(tmp);
	}
	free(node);
}

void	free_env(t_env *env)
{
	t_env	*next;
	t_env	*tmp;

	next = NULL;
	if (env)
	{
		next = env->next;
		free(env->name);
		free(env->value);
		free(env);
	}
	while (next)
	{
		// if (env == env->next)
		// 	env->next = NULL;
		tmp = next;
		next = next->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
