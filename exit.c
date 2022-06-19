/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:19:10 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/17 19:12:03 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_nb(char *str)
{
	long long	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

void	exit_shell(char **str, int i)
{
	char	*trim;

	if (str[1])
		i = ft_atoi(str[1]);
	trim = ft_strtrim(str[1], "\'\"");
	if (trim)
	{
		if (trim[0] == '-' && str[2] == NULL)
			exit(255);
		if (check_if_nb(trim) == 0 || ft_strlen(trim) >= 19)
		{
			printf("exit: %s: numeric argument required\n", trim);
			var.exit_code = 255;
			exit(var.exit_code);
		}
		if (str[2])
		{
			printf("exit: too many arguments\n");
			return ;
		}
	}
	var.exit_code = i;
	exit(var.exit_code);
}
