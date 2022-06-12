/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:54:42 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/12 19:32:43 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_envp(t_env *env)
{
	char	**temp_envp;
	char	*tmp_name;
	int		i;
	int		len;
	char	*str;
		///leaks in join and strdup here
	str = ft_strdup("");
	len = list_len(env);
	i = 0;
	temp_envp = malloc(sizeof(char *) * len + 1);
	if (!temp_envp)
		exit (EXIT_FAILURE);
	while (env)
	{
		tmp_name = ft_strjoin(env->name, "=");
		if (temp_envp[i] != NULL && env->value)
			temp_envp[i] = ft_strjoin(tmp_name, env->value);
		else
			temp_envp[i] = ft_strjoin(tmp_name, str);
		if (tmp_name)
			free(tmp_name);
		if (env->next)
		{
			i++;
			env = env->next;
		}
		else //if (--len == 0 )
			break ;
	}
	free(str);
	temp_envp[i + 1] = NULL;
	return (temp_envp);
}

t_env	*remove_last_env(t_env **env, char *tmp_cmd)
{
	// while (env)
	// {
	// 	if (env->next && !ft_strcmp(env->next->name, tmp_cmd))
	// 	{
		(void)tmp_cmd;
			t_env	*tmp;

			tmp = *env;
			if (*env != NULL)
				*env = (*env)->prev;
			if (*env != NULL)
				(*env)->next = NULL;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			tmp = NULL;
			return (tmp);
			// break ;
		// }
		// if (env->next)
		// 	env = env->next;
		// else
		// 	break ;
}

void	remove_env(char *name, t_env **env, char **envp)
{
	t_env	*tmp;
	// t_env	*tmp1;

	tmp = *env;
	(void)envp;
	// if (!ft_strcmp((*env)->name, name))
	// {
	// 	free_env(env, name);
	// 	(void)envp;
	// 	// tmp = *env;
	// 	// tmp = get_env(envp, 1);
	// 	return ;
	// }
	while (ft_strcmp((*env)->name, name))
		*env = (*env)->next;
	free_env(env);
	// tmp1 = (*env)->next->next;
	// free((*env)->next->name);
	// free((*env)->next->value);
	// free((*env)->next);
	// (*env)->next = tmp1;
	return ;
}
