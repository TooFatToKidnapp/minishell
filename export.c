/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:00:27 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/30 19:30:03 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_len()

void	sort_and_print_env(t_env *env)
{
	char	**tmp_str;
	int		i;

	tmp_str = sort_tmp_str(env, list_len(env));
}

void	export(t_env *env, char **str, char **envp)
{
	int		i;
	char	**tmp_envp;

	if (str[1] == '\0')
		sort_and_print_env(env);
}
