/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:45:57 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/30 14:51:25 by aabdou           ###   ########.fr       */
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
		return(perror("Error malloc"), exit(EXIT_FAILURE));
	var->value = get_value(str);
	var->name = get_name(str);
	var->next = NULL;
	if ((*env) == NULL)
	{
		*env = var;
		return ;
	}
	head = *env;
	while (head->next)
		head = head->next;
	head->next = var;
	return ;
}

t_env	*get_env(char **envp)
{
	t_env	*env;
	char	cwd[1024];
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		add_var(&env, envp[i]);
		i++;
	}
	if (envp[0] == NULL)
	{
		getcwd(cwd, 1024);
		env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			return (perror("Error malloc"), exit(EXIT_FAILURE), NULL);
		env->name = ft_strdup("PWD");
		env->value = ft_strdup(cwd);
		env->next = NULL;
	}
	return (env);
}

void	print_env(t_env *env)
{
	while(env != NULL)
	{	if (env->value != NULL)
			printf("%s=%s\n", env->name, env->value);
		if (env->next != NULL)
			env = env->next;
		else
			break;
	}
}
