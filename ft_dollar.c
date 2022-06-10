/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:25:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/09 19:33:57 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*triming(char *str)
{
	char	*hub;

	if (str[0] == '\"')
		hub = ft_strtrim(str, "\"");
	else if (str[0] == '\'')
		hub = ft_strtrim(str, "\'");
	else
		hub = ft_strdup(str);
	free(str);
	return (hub);
}

void	ft_if(int change, char *tab, char **str, char *dollar)
{
	char	*hub;
	char	*tmp;

	if (change == 0 && ft_dollar_only(tab) == 0)
	{
		hub = ft_strdup("\0");
		free(*str);
		tmp = ft_strjoin(dollar, " ");
		*str = ft_strjoin(tmp, hub);
		free(tmp);
		free(hub);
	}
}

void	change_value(char **str, int index, t_env *env)
{
	t_env	*head;
	char	**dollar;
	char	*tab;
	int		change;

	change = 0;
	dollar = ft_split(str[index], ' ');
	if (dollar == NULL)
		return (printf("malloc error\n"), exit(1));
	tab = ft_dollar(dollar);
	tab = triming(tab);
	head = env;
	while (env)
	{
		if (!ft_strncmp(env->name, tab + 1, ft_strlen(tab + 1) + 1))
		{
			change = ft_switch(env, dollar, &str[index]);
			break ;
		}
		env = env->next;
	}
	ft_if(change, tab, &str[index], dollar[0]);
	free(tab);
	free_2d(dollar);
	env = head;
}

void	change_value_exit(char **str, int index)
{
	char	**dollar;
	char	*tab;
	char	*tmp;

	dollar = ft_split(str[index], ' ');
	if (dollar == NULL)
		return (printf("malloc error\n"), exit(1));
	tab = ft_itoa(var.exit_code);
	free(str[index]);
	tmp = ft_strjoin(dollar[0], " ");
	str[index] = ft_strjoin(tmp, tab);
	free(tab);
	free(tmp);
	free_2d(dollar);
}

void	check_dollar(char **str, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '$' && str[i][j] != '\0')
			j++;
		if (str[i][j] == '$' && str[i][j + 1] != '?')
		{
			if (!(str[i][j - 1] == '\'' && str[i][j - 2] == ' '))
				change_value(str, i, env);
		}
		else if (str[i][j] == '$' && str[i][j + 1] == '?')
		{
			if (!(str[i][j - 1] == '\'' && str[i][j - 2] == ' '))
				change_value_exit(str, i);
		}
		i++;
	}
}
