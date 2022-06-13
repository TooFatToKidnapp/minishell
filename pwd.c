/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:49:59 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/13 17:41:03 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	str[1024];

	getcwd(str, 1024);
	return (ft_strdup(str));
}

void	pwd(void)
{
	char	str[1024];

	getcwd(str, 1024);
	printf("%s\n", str);
	var.exit_code = 0;
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->name, env->value);
		if (env->next != NULL)
			env = env->next;
		else
			break ;
	}
	var.exit_code = 0;
}

void	check_and_change2(t_env **env, char *name, char *value)
{
	while (env != NULL && (*env)->next != NULL)
	{
		if (ft_strcmp((*env)->name, name) == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
			break;
		}
		*env = (*env)->next;
	}
}
