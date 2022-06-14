/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:14:55 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/14 15:46:33 by aabdou           ###   ########.fr       */
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

void	free_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp2 = (*env)->next;
	tmp1 = (*env)->prev;
	free((*env)->name);
	free((*env)->value);
	free((*env));
	*env = NULL;
	if (tmp1 == NULL && tmp2)
	{
		(*env) = tmp2;
		(*env)->prev = NULL;
	}
	else if (!tmp2 && tmp1)
	{
		tmp1->next = NULL;
		(*env) = tmp1;
	}
	if (tmp1 && tmp2)
	{
		tmp1->next = tmp2;
		tmp2->prev = tmp1;
		(*env) = tmp1;
	}
}

void	free_all_env(t_env *env)
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
		tmp = next;
		next = next->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
