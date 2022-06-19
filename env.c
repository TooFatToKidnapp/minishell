/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:45:57 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/14 18:39:55 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_value(char *str)
{
	int	start;
	int	len;
	int	i;

	start = 0;
	len = 0;
	while (str[start] && str[start] != '=')
		start++;
	start++;
	i = start;
	while (str[i])
	{
		i++;
		len++;
	}
	return (ft_substr(str, start, len));
}

void	add_var(t_env **env, char *str)
{
	t_env	*var;
	t_env	*head;

	var = (t_env *)malloc(sizeof(t_env));
	if (var == NULL)
		return (perror("Error malloc"), exit(EXIT_FAILURE));
	var->value = get_value(str);
	var->name = get_name(str);
	var->next = NULL;
	var->prev = NULL;
	if ((*env) == NULL)
	{
		*env = var;
		return ;
	}
	head = *env;
	while (head->next)
		head = head->next;
	head->next = var;
	var->prev = head;
	return ;
}

t_env	*get_env(char **envp, int flag)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		add_var(&env, envp[i]);
		i++;
	}
	if (flag != 1 && envp[0] == NULL)
		env = create_path_pwd();
	return (env);
}

t_env	*create_path_pwd(void)
{
	char	cwd[1024];
	t_env	*env;
	t_env	*env2;

	getcwd(cwd, 1024);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (perror("Error malloc"), exit(EXIT_FAILURE), NULL);
	env->name = ft_strdup("PWD");
	env->value = ft_strdup(cwd);
	env2 = (t_env *)malloc(sizeof(t_env));
	if (!env2)
		return (perror("Error malloc"), exit(EXIT_FAILURE), NULL);
	env2->name = ft_strdup("PATH");
	env2->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env->next = env2;
	env2->next = NULL;
	env->prev = NULL;
	env2->prev = env;
	return (env);
}
