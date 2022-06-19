/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:38:23 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/18 13:31:44 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_valid(char *vars)
{
	int	i;

	i = 0;
	while (vars[i])
	{
		if (!ft_isalpha(vars[i]) && vars[i] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", vars);
			var.exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	unset(t_env **env, char **cmd)
{
	int		i;
	char	*tmp_cmd;

	i = 1;
	while (cmd[i])
	{
		tmp_cmd = ft_strtrim(cmd[i], "\"\'");
		if (check_if_valid(tmp_cmd))
		{
			free(tmp_cmd);
			return ;
		}
		remove_env(cmd[i], env);
		free(tmp_cmd);
		i++;
	}
	var.exit_code = 0;
	return ;
}
