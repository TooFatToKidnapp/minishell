/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:56:24 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/08 12:10:04 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkflag(char *str)
{
	int	i;

	i = 1;
	if(str[1] == '\0')
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
		if (line[i][0] == '\'')
			tmp = ft_strtrim(line[i], "\'");
		else if (line[i][0] == '\"')
			tmp = ft_strtrim(line[i], "\"");
		else
			tmp = ft_strdup(line[i]);
		if (i != flag)
			printf(" ");
		printf("%s", tmp);
		i++;
		free(tmp);
	}
	if (flag == 1)
		printf("\n");
}
