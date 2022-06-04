/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:49:59 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/02 17:36:45 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char str[1024];
	getcwd(str, 1024);
	return(ft_strdup(str));
}

void	pwd(void)
{
	char str[1024];
	getcwd(str, 1024);
	printf("%s\n", str);
}

void	print_env(t_env *env)
{
	while(env != NULL)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->name, env->value);
		if (env->next != NULL)
			env = env->next;
		else
			break;
	}
}
