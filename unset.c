/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:38:23 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/09 12:30:10 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(t_env *env, char **envp)
{
	char	**tmp_envp;
	int		i;
	int		len;

	len = 0;
	i = 0;
	tmp_envp = new_envp(env);
	while (tmp_envp[i])
	{
		len = ft_strlen(tmp_envp[i]) + 1;
		ft_strlcpy(envp[i], tmp_envp[i], len);
		i++;
	}
	free_2D(tmp_envp);
	envp[i] = NULL;
}

t_env	*delete_env(t_env *env, t_env *tmp, char *tmp_cmd, char **envp)
{
	while (env->next)
	{
		if (!ft_strcmp(env->name, tmp_cmd))
		{
			tmp = remove_env(env->name, tmp, envp);
			break;
		}
		env = env->next;
	}
	if (!env->next)
	{
		env = tmp;
		remove_last_env(env, tmp_cmd);
	}
	return (tmp);
}

int	check_if_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && var[i] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", var);
			return 1;
		}
		i++;
	}
	return 0;
}

t_env	*unset(t_env *env, char **cmd, char **envp)
{
	int		i;
	char	*tmp_cmd;
	t_env	*tmp;
	(void)envp;
	i = 1;
	tmp = env;
	while (cmd[i])
	{
		tmp_cmd = ft_strtrim(cmd[i], "\"\'");
		if (check_if_valid(tmp_cmd))
		{
			free(tmp_cmd);
			return(tmp);
		}
		tmp = delete_env(env, tmp, tmp_cmd, envp);
		free(tmp_cmd);
		env = tmp;
		i++;
	}
	env = tmp;
	// update_envp(env, envp);
	return tmp;
}
