/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:06:45 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/05 16:38:06 by aabdou           ###   ########.fr       */
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

char	**sort_2D_str(t_env *node, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	**tmp_2D;

	tmp_2D = fill_2D(node, len);
	i = -1;
	j = 0;
	while(++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (tmp_2D[j] && ft_strcmp(tmp_2D[i], tmp_2D[j]) > 0)
			{
				tmp = ft_strdup(tmp_2D[i]);
				free(tmp_2D[i]);
				tmp_2D[i] =ft_strdup(tmp_2D[j]);
				free(tmp_2D[j]);
				tmp_2D[j] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	tmp_2D[i] = NULL;
	return (tmp_2D);
}

char	**fill_2D(t_env *node, int len)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * len + 1);
	if (tmp == NULL)
		return (perror("Error Malloc"), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (node != NULL)
	{
		tmp = fill_block_in_2D(node, i, tmp);
		i++;
		if (node->next)
			node = node->next;
		else
			break;
	}
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**fill_block_in_2D(t_env *node, int i, char **tmp)
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
		str = ft_strjoin(tmp_name,tmp_value);
		free(tmp_name);
		free(tmp_value);
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

int	ft_add_to_env(t_env *env, char *str, int i, int equal_pos)
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
	while (value && str[++equal_pos])
		value[i++] = str[equal_pos];
	if (i != 0)
		value[i] = '\0';
	update_env(env, trimed_name, value);
	free(trimed_name);
	if (value)
		free(value);
	return (0);
}
