/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:54:42 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/10 17:10:05 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_envp(t_env *env)
{
	char	**temp_envp;
	char	*tmp_name;
	int		i;
	int		len;

	len = list_len(env);
	i = 0;
	temp_envp = malloc(sizeof(char *) * len + 1);
	if (!temp_envp)
		exit (EXIT_FAILURE);
	while (env)
	{
		tmp_name = ft_strjoin(env->name, "=");
		if (temp_envp[i] != NULL && tmp_name && env->value)
			temp_envp[i] = ft_strjoin(tmp_name, env->value);
		else
			temp_envp[i] = ft_strjoin(tmp_name, ft_strdup(""));
		if (tmp_name)
			free(tmp_name);
		if (env->next)
		{
			i++;
			env = env->next;
		}
		else if (--len == 0 )
			break ;
	}
	temp_envp[i + 1] = NULL;
	return (temp_envp);
}

void	remove_last_env(t_env *env, char *tmp_cmd)
{
	while (env)
	{
		if (env->next && !ft_strcmp(env->next->name, tmp_cmd))
		{
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = NULL;
			break ;
		}
		if (env->next)
			env = env->next;
		else
			break ;
	}
}

t_env	*remove_env(char *name, t_env *env, char **envp)
{
	t_env	*tmp;

	tmp = env;
	if (!ft_strcmp(env->name, name))
	{
		free_env(env);
		tmp = get_env(envp + 1);
		return (tmp);
	}
	while (ft_strcmp(env->next->name, name))
		env = env->next;
	free(env->next->name);
	free(env->next->value);
	free(env->next);
	env->next = env->next->next;
	return (tmp);
}
