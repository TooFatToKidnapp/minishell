/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:19:10 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/09 12:05:53 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(char **str, int i)
{
	char	*trim;

	printf("exit\n");
	trim = ft_strtrim(str[1], "\'\"");
	if (trim && !ft_isdigit(trim[0]) && trim[0] != '-' && trim[0] != '+')
	{
		printf("exit: %s: numeric argument required\n", trim);
		exit(EXIT_SUCCESS);
	}
	if (str[1] && str[2])
	{
		printf("exit: too many arguments\n");
		free(trim);
		return ;
	}
	while (trim && trim[++i])
	{
		if (!ft_isdigit(trim[i]) && trim[i] != '\'' && trim[i] != '"')
		{
			printf("exit: %s: numeric argument required\n", trim);
			break;
		}
	}
	exit(EXIT_SUCCESS);
}
