/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:37:39 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/04 22:38:03 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_equal_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break;
		i++;
	}
	return (i);
}

void	allocate(char **name, char **value, char *str, int pos)
{
	(*name) = malloc(sizeof(char) * pos + 1);
	if ((*name) == NULL)
		exit(EXIT_FAILURE);
	if (pos == (int)ft_strlen(str))
		(*value) = NULL;
	else
	{
		(*value) = malloc(sizeof(char) * ((ft_strlen(str) - pos) + 1));
		if ((*value) == NULL)
			exit(EXIT_FAILURE);
	}
}

int	check_identifier(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
			printf("export: `%s': not a valid identifier\n", str);
			return (1);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (printf("export1: `%s': not a valid identifier\n", str), 1);
		i++;
	}
	return (0);
}

void	new_env(char *name, char *value, t_env *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit (EXIT_FAILURE);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	env->next = new;
}

void	*update_env(t_env *env, char *name, char *value)
{
	char	*trimd_value;

	trimd_value = ft_strtrim(value, "\"\'");
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			if (!value && ((env->value && env->value[0] == '\0') || !env->value))
				return (NULL);
			else if (trimd_value)
			{
				if (env->value)
					free(env->value);
				env->value = ft_strdup(trimd_value);
				return(free(trimd_value), NULL);
			}
		}
		if (env->next)
			env = env->next;
		else
			break;
	}
	if (env && !env->next)
		new_env(name, trimd_value, env);
	return(free(trimd_value), NULL);
}
