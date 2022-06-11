/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:38:23 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/11 14:28:17 by aabdou           ###   ########.fr       */
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
			strlcpy(envp[i], t_envp, len);
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

t_env	*unset(t_env *env, char **cmd, char **envp)
{
	int		i;
	char	*tmp_cmd;
	t_env	*tmp;

	i = 1;
	tmp = env;
	while (cmd[i])
	{
		tmp_cmd = ft_strtrim(cmd[i], "\"\'");
		if (check_if_valid(tmp_cmd))
		{
			free(tmp_cmd);
			return (tmp);
		}
		tmp = delete_env(env, tmp, tmp_cmd, envp);
		free(tmp_cmd);
		env = tmp;
		i++;
	}
	env = tmp;
	// int j = 0;
	// while(env)
	// {
	// 	printf("%d\n", j++);
	// 	printf("env adress %p   %s=%s  %p\n", env ,env->name, env->value, tmp->next);
	// 	env = env->next;
	// }
	update_envp(env, envp);
	var.exit_code = 0;
	return (tmp);
}
