/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:22:28 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/05 20:21:52 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**trim_str(char **tab)
{
	char	**str;
	int		i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	str = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i] != NULL)
	{
		str[i] = ft_strtrim(tab[i], " ");
		i++;
	}
	str[i] = NULL;
	return (str);
}

// split the command b4 '|' and store each element in a 2d array inside a node , return a pointer to that node
t_node	*create_and_fill(char *cmd, int index)
{
	t_node	*new;
	char	**str;
	int 	i;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		return (perror("Error node"), exit(EXIT_FAILURE), NULL);
	str = ft_split(cmd, ' ');
	i = 0;
	while(str[i])
		i++;
	new->arg = malloc(sizeof(char *) * i + 1);
	if (new->arg == NULL)
		return (perror("Error node"), free_2D(str), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (str[i])
	{
		new->arg[i] = ft_strdup(str[i]);
		i++;
	}
	new->arg[i] = NULL;
	new->next = NULL;
	new->index = index;
	free_2D(str);
	return (new);
}

t_node	*add_node_back(t_node *node) // return the last node
{
	if (node == NULL)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void	add_node(t_node **node, t_node *new)
{
	t_node	*last;

	if ((*node) == NULL) //if list is empty new becomes the first node
		*node = new;
	else	// else it becomse the last
	{
		last = add_node_back(*node);
		last->next = new;
		new->prev = last;
	}
}

void	fill_node(char **str, t_node **node)
{
	int	i;

	i = 0;
	while(str[i])
	{
		add_node(node, create_and_fill(str[i], i));
		i++;
	}
}
