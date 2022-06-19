/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:37:39 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/17 19:20:57 by hmoubal          ###   ########.fr       */
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
			break ;
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
	int	i;

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

void	new_env(char *name, char *value, t_env **env)
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
	if (*env != NULL)
	{
		(*env)->next = new;
		new->prev = (*env);
	}
	else if (*env == NULL)
	{
		*env = new;
		new->prev = NULL;
	}
}

void	*update_env(t_env **env, char *name, char **value)
{
	char	*tr_val;

	tr_val = ft_strtrim(*value, "\"\'");
	while (*env)
	{
		if (!ft_strcmp(name, (*env)->name))
		{
			if ((!tr_val && (((*env)->value && (*env)->value[0] == '\0')
						|| !(*env)->value)) || ((*env)->value && !tr_val))
				return (NULL);
			else if (tr_val)
			{
				if ((*env)->value)
					free((*env)->value);
				return ((*env)->value = ft_strdup(tr_val), free(tr_val), NULL);
			}
		}
		if ((*env)->next)
			(*env) = (*env)->next;
		else
			break ;
	}
	if (*value)
		free(*value);
	return (new_env(name, tr_val, env), free(tr_val), NULL);
}
