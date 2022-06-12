/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:38:23 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/12 21:44:39 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(t_env *env, char **envp)
{
	char	**tmp_envp;
	int		i;
	int		len;
	char	*str = strdup("");
	char	*t_envp;

	len = 0;
	i = 0;
	tmp_envp = new_envp(env);
	while (tmp_envp[i])
	{
		len = (strlen(tmp_envp[i]) + 1);
		if(tmp_envp[i] != NULL && envp[i])
		{
			t_envp = strdup(tmp_envp[i]);
			ft_strlcpy(envp[i], t_envp, len);
			free(t_envp);
			//envp[i] = ft_strdup(tmp_envp[i]);
		}
		else if (envp[i] != NULL)
			ft_strlcpy(envp[i], str, len);
			//envp[i] = ft_strdup("");
		i++;
	}
	free(str);
	free_2d(tmp_envp);
	envp[i] = NULL;
}

void	delete_env(t_env **env, char *tmp_cmd, char **envp)
{
	while (*env)
	{
		if (!ft_strcmp((*env)->name, tmp_cmd))
		{
			remove_env((*env)->name, env, envp);
			break ;
		}
		*env = (*env)->next;
	}
}

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

void	unset(t_env **env, char **cmd, char **envp)
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
		remove_env(cmd[i], env, envp);
		free(tmp_cmd);
		i++;
	}
	var.exit_code = 0;
	return ;
}
