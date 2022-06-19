/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:54:42 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/18 13:30:40 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_last_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (*env != NULL)
		*env = (*env)->prev;
	if (*env != NULL)
		(*env)->next = NULL;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	tmp = NULL;
	return (tmp);
}

void	remove_env(char *name, t_env **env)
{
	t_env	*head;

	head = *env;
	while (*env)
	{
		if (!ft_strcmp((*env)->name, name))
		{
			free_env(env);
			return ;
		}
		*env = (*env)->next;
	}
	if (*env == NULL)
		*env = head;
	return ;
}
