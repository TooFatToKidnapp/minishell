/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:49:59 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/11 19:10:24 by hmoubal          ###   ########.fr       */
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
