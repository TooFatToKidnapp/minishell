/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:56:24 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/17 18:20:47 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkflag(char *str)
{
	int	i;

	i = 1;
	if (str[1] == '\0')
		return (1);
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo(char **line)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = 1;
	while (line[flag] != NULL && ft_checkflag(line[flag]) == 0)
		flag++;
	i = flag;
	while (line && line[i])
	{
		tmp = ft_strdup(line[i]);
		if (i != flag)
			printf(" ");
		printf("%s", tmp);
		i++;
		free(tmp);
	}
	if (flag == 1)
		printf("\n");
	var.exit_code = 0;
}
