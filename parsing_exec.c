/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:51:15 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/08 11:53:18 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fill_arg(t_args commands, t_node node)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (node.arg[i] != NULL)
	{
		if (strncmp(node.arg[i], "<", 2) == 0)
			i += 2;
		else if (strncmp(node.arg[i], "<<", 3) == 0)
			i += 2;
		else if (strncmp(node.arg[i], ">", 2) == 0)
			i += 2;
		else if (strncmp(node.arg[i], ">>", 3) == 0)
			i += 2;
		else
		{
			commands.cmd[k] = ft_strdup(node.arg[i]);
			if (commands.cmd[k] == NULL)
				return (printf("malloc error\n"), exit(1));
			k++;
			i++;
		}
	}
}

void	init_cmd(t_node *node, t_args *commands, int size)
{
	int	i;
	int	count_cmd;

	i = 0;
	while (i < size)
	{
		count_cmd = 0;
		while (node->arg[count_cmd] != NULL)
			count_cmd++;
		if (commands[i].infile == 2)
			count_cmd -= 2;
		if (commands[i].outfile == 2)
			count_cmd -= 2;
		if (commands[i].outappend == 2)
			count_cmd -= 2;
		if (commands[i].here_doc == 2)
			count_cmd -= 2;
		commands[i].cmd = (char **)malloc(sizeof(char *) * count_cmd + 1);
		if (commands[i].cmd == NULL)
			return (printf("malloc error\n"), exit(1));
		commands[i].cmd[count_cmd] = NULL;
		fill_arg(commands[i], *node);
		node = node->next;
		i++;
	}
}

void	init_args(t_args *commands, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		commands[i].here_doc = 0;
		commands[i].infile = 0;
		commands[i].outappend = 0;
		commands[i].outfile = 0;
		commands[i].limiter = NULL;
		commands[i].in_file = NULL;
		commands[i].out_append = NULL;
		commands[i].out_file = NULL;
		i++;
	}
}

t_args	*parse_arg(t_node *node)
{
	t_args	*commands;
	t_node	*head;
	int		index;

	commands = (t_args *)malloc(sizeof(t_args) * lst_size(node));
	if (commands == NULL)
	{
		printf("no more space\n");
		exit(1);
	}
	init_args(commands, lst_size(node));
	head = node;
	index = ft_while(node, commands);
	node = head;
	init_cmd(node, commands, index);
	return (commands);
}

void	free_inside(t_args commands)
{
	if (commands.infile != 0)
		free(commands.in_file);
	if (commands.outappend != 0)
		free(commands.out_append);
	if (commands.outfile != 0)
		free(commands.out_file);
	if (commands.here_doc != 0)
		free(commands.limiter);
}
