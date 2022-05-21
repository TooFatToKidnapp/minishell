/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:14:55 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/21 15:14:56 by aabdou           ###   ########.fr       */
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
		return ;
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
