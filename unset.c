/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:38:23 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/12 19:31:29 by hmoubal          ###   ########.fr       */
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
	t_env	*tmp;

	i = 1;
	tmp = *env;
	while (cmd[i])
	{
		tmp_cmd = ft_strtrim(cmd[i], "\"\'");
		if (check_if_valid(tmp_cmd))
		{
			free(tmp_cmd);
			return ;
		}
		remove_env(cmd[i], env, envp);
		// delete_env(env, tmp_cmd, envp);
		free(tmp_cmd);
		i++;
	}
	// int j = 0;
	// while(env)
	// {
	// 	printf("%d\n", j++);
	// 	printf("env adress %p   %s=%s  %p\n", env ,env->name, env->value, tmp->next);
	// 	env = env->next;
	// }
	// update_envp(*env, envp);
	var.exit_code = 0;
	return ;
}
