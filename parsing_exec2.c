/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:12:29 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/07 16:18:17 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_parse_part2(t_args *commands, t_node *node, int index, int i)
{
	if (commands[index].infile == 1)
	{
		commands[index].in_file = ft_strdup(node->arg[i]);
		commands[index].infile++;
	}
	else if (commands[index].here_doc == 1)
	{
		commands[index].limiter = ft_strdup(node->arg[i]);
		commands[index].here_doc++;
	}
	else if (commands[index].outfile == 1)
	{
		commands[index].out_file = ft_strdup(node->arg[i]);
		commands[index].outfile++;
	}
	else if (commands[index].outappend == 1)
	{
		commands[index].out_append = ft_strdup(node->arg[i]);
		commands[index].outappend++;
	}
}

int	ft_while(t_node *node, t_args *commands)
{
	int	index;
	int	i;

	index = 0;
	while (node != NULL)
	{
		i = 0;
		while (node->arg[i] != NULL)
		{
			if (strncmp(node->arg[i], "<", 2) == 0)
				commands[index].infile = 1;
			else if (strncmp(node->arg[i], "<<", 3) == 0)
				commands[index].here_doc = 1;
			else if (strncmp(node->arg[i], ">", 2) == 0)
				commands[index].outfile = 1;
			else if (strncmp(node->arg[i], ">>", 3) == 0)
				commands[index].outappend = 1;
			else
				ft_parse_part2(commands, node, index, i);
			i++;
		}
		node = node->next;
		index++;
	}
	return (index);
}
