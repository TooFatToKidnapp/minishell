/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:06:45 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/12 22:15:19 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_len(t_env *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

char	**sort_2d_str(t_env *node, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	**tmp_2d;

	tmp_2d = fill_2d(node, len);
	i = -1;
	j = 0;
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (tmp_2d[j] && ft_strcmp(tmp_2d[i], tmp_2d[j]) > 0)
			{
				tmp = ft_strdup(tmp_2d[i]);
				free(tmp_2d[i]);
				tmp_2d[i] = ft_strdup(tmp_2d[j]);
				free(tmp_2d[j]);
				tmp_2d[j] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	return (tmp_2d[i] = NULL, tmp_2d);
}

char	**fill_2d(t_env *node, int len)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (perror("Error Malloc"), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (node != NULL)
	{
		tmp = fill_block_in_2d(node, i, tmp);
		i++;
		if (node->next)
			node = node->next;
		else
			break ;
	}
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**fill_block_in_2d(t_env *node, int i, char **tmp)
{
	char	*tmp_name;
	char	*tmp_value;
	char	*str;
	char	*value;

	if (node->value)
	{
		tmp_name = ft_strjoin(node->name, "=");
		value = ft_strjoin("\"", node->value);
		tmp_value = ft_strjoin(value, "\"");
		free(value);
		str = ft_strjoin(tmp_name, tmp_value);
		free(tmp_value);
		free(tmp_name);
	}
	else
	{
		tmp_name = ft_strdup(node->name);
		str = ft_strdup(tmp_name);
		free(tmp_name);
	}
	tmp[i] = ft_strjoin("declare -x ", str);
	free(str);
	return (tmp);
}

int	ft_add_to_env(t_env **env, char *str, int i, int equal_pos)
{
	char	*name;
	char	*trimed_name;
	char	*value;

	equal_pos = get_equal_pos(str);
	allocate(&name, &value, str, equal_pos);
	i = -1;
	while (++i < equal_pos)
		name[i] = str[i];
	name[i] = '\0';
	trimed_name = ft_strtrim(name, "\"\'");
	free(name);
	if (check_identifier(trimed_name))
		return (free(trimed_name), free(value), 0);
	i = 0;
	while (value && str[equal_pos])
		value[i++] = str[++equal_pos];
	if (i != 0)
		value[i] = '\0';
	update_env(env, trimed_name, value);
	free(trimed_name);
	if (value)
		free(value);
	if (*env != NULL)
	{
		while((*env)->prev != NULL)
			*env = (*env)->prev;
	}
	return (0);
}
