/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:28:52 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/09 19:29:24 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dollar(char **dollar)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	tab = NULL;
	while (dollar[i] != NULL)
	{
		j = 0;
		while (dollar[i][j] != '\0')
		{
			if (dollar[i][j] == '$')
			{
				tab = ft_strdup(dollar[i]);
				return (tab);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

int	ft_switch(t_env *env, char **dollar, char **str)
{
	int		change;
	char	*tab;
	char	*tmp;

	change = 0;
	tab = NULL;
	tmp = NULL;
	if (env->value != NULL)
	{
		tab = ft_strdup(env->value);
		free(*str);
		tmp = ft_strjoin(dollar[0], " ");
		*str = ft_strjoin(tmp, tab);
		change = 1;
	}
	else if (env->value == NULL)
	{
		tab = ft_strdup("\0");
		free(*str);
		tmp = ft_strjoin(dollar[0], " ");
		*str = ft_strjoin(tmp, tab);
		change = 1;
	}
	return (free(tmp), free(tab), change);
}

int	ft_dollar_only(char *dollar)
{
	int	i;

	i = 0;
	while (dollar[i] != '\0')
	{
		if (dollar[i] == '$' && dollar[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}
