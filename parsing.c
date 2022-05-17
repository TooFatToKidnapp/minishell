/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:21:18 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/17 18:56:18 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	**parser(t_node **node)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(var.user_input, " ");
	printf("-%s-\n" ,str);
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (var.user_input != '\0')
	{
		node = check_err();
	}
	free(str);
	return (node);
}

t_node	**check_err(void)
{
	t_node	**node;
	int		i;

	i = 0;
	 node = malloc(sizeof(t_node *));
	if (node == NULL)
	{
		return(ft_putstr_fd("Error\n", 2), exit(EXIT_FAILURE), NULL);
	}
	*node = NULL;
	if(check_pipes() == 0 || check_quotes() == 0 || check_directions() == 0)
		printf("ERROR----\n");
	return node;
}

