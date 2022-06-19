/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:28:52 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:41:18 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	change_tilda(t_lists *top, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->name))
		{
			free(top->value);
			top->value = ft_strdup(tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
}

int	change_value2(char **str, t_env *env)
{
	t_env	*tmp;
	int		change;

	change = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(*str + 1, tmp->name))
		{
			free(*str);
			*str = ft_strdup(tmp->value);
			change = 1;
			break ;
		}
		else if (!ft_strncmp(*str + 2, tmp->name, ft_strlen(tmp->name)))
		{
			free(*str);
			*str = ft_strjoin("'", tmp->value);
			*str = ft_strjoin_gnl(*str, "'");
			change = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (change);
}

void	fill_value(char **str, t_lists **top)
{
	char	*value;
	int		i;

	i = 1;
	if (str[0][0] != '\0')
		value = ft_strdup(str[0]);
	else
		value = ft_strdup("");
	while (str[i] != NULL)
	{
		if (str[i][0] != '\0')
		{
			if (value[0] != '\0')
				value = ft_strjoin_gnl(value, " ");
			value = ft_strjoin_gnl(value, str[i]);
		}
		i++;
	}
	(*top)->value = ft_strdup(value);
	free(value);
}

void	change_value(t_lists *top, t_env *env)
{
	char	**str;
	int		i;

	str = ft_split(top->value, ' ');
	free(top->value);
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '$' && str[i][1] != '\0')
		{
			if (change_value2(&str[i], env) == 0)
			{
				free(str[i]);
				str[i] = ft_strdup("");
			}
		}
		i++;
	}
	fill_value(str, &top);
	free_2d(str);
}

void	expansion(t_lists **head, t_env *env)
{
	t_lists	*top;

	top = *head;
	while (top)
	{
		if (ft_strncmp(top->value, "$", 2) != 0)
		{
			if (top->type == TOKEN_WORD && !int_strchr(top->value, '?'))
			{
				free(top->value);
				top->value = ft_itoa(var.exit_code);
			}
			else if (top->type == TOKEN_TILDA && !int_strchr(top->value, '~'))
				change_tilda(top, env);
			else if (top->type != TOKEN_STR && !int_strchr(top->value, '$'))
				change_value(top, env);
		}
		top = top->next;
	}
}
