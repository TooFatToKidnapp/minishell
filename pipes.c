/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:11:16 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/09 19:17:43 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_start_and_end(void)
{
	char	*str;

	str = ft_strtrim(var.user_input, " ");
	if (str[0] == '|')
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		var.exit_code = 258;
		free(str);
		return (0);
	}
	else if (str[ft_strlen(str)-1] == '|')
	{
		printf("Minishell: syntax error near unexpected end of command\n");
		var.exit_code = 258;
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

int	check_pipes_back_to_back(void)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strchr(var.user_input, '|');
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		var.exit_code = 258;
		return (0);
	}
	return (1);
}

int	check_pipes(void)
{
	char	*str;

	str = ft_strchr(var.user_input, '|');
	if (str == NULL)
		return (1);
	if (check_start_and_end() == 0 || check_pipes_back_to_back() == 0)
		return (0);
	str++;
	while (*str != '\0')
	{
		while (*str == ' ')
			str++;
		if (*str == '|')
		{
			var.exit_code = 258;
			return (printf("Minishell: syntax error"
					"near unexpected token `|'\n"), 0);
		}
		str = ft_strchr(str, '|');
		if (str == NULL)
			break ;
		str++;
	}
	return (1);
}
