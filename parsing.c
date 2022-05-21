/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:21:18 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/21 15:17:17 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	**parser(t_node **node)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(var.user_input, " ");
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	free(str);
	if (var.user_input != '\0')
	{
		node = check_err();
	}
	return (node);
}

t_node	**check_err(void)
{
	t_node	**node;
	int		i;
	char	**command;
	char	**str;

	i = 0;
	node = malloc(sizeof(t_node *));
	if (node == NULL)
	{
		return(ft_putstr_fd("Error\n", 2), exit(EXIT_FAILURE), NULL);
	}
	*node = NULL;
	if(check_pipes() == 0 || check_quotes() == 0 || check_directions() == 0)
		return(NULL);
	command = ft_split(var.user_input, '|');
	str = trim_str(command);
	free_2D(command);
	if (check_red_pos(str) == 0)
		return (free_2D(str), NULL);
	fill_node(str,node);
	// int j = 0;
	// while((*node))
	// {
	// 	while((*node)->arg[j])
	// 	{
	// 		printf("-%s-\n", (*node)->arg[j]);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	*node = (*node)->next;
	// }
	free_2D(str);
	return node;
}

