/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:21:18 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/07 23:21:19 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	**parser(t_node **node)
{
	char	*str;

	str = ft_strtrim(var.user_input, " ");
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	free(str);
	if (var.user_input != NULL)
	{
		node = check_err();
	}
	return (node);
}

t_node	**check_err(void)
{
	t_node	**node;
	char	**command;
	char	**str;

	node = malloc(sizeof(t_node *));
	if (node == NULL)
	{
		return(ft_putstr_fd("Error\n", 2), exit(EXIT_FAILURE), NULL);
	}
	*node = NULL;
	if(check_pipes() == 0 || check_quotes() == 0 || check_directions() == 0)
		return(free_list(node) ,NULL);
	command = ft_split(var.user_input, '|');
	str = trim_str(command);
	free_2D(command);
	if (check_red_pos(str) == 0)
		return (free_2D(str), free_list(node), NULL);
	fill_node(str,node);
	free_2D(str);
	return node;
}

// fix echo echo "'" && "''"
