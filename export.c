/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:00:27 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/01 13:53:01 by aabdou           ###   ########.fr       */
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
		tmp_name = ft_strdup(tmp_name);
		str = ft_strdup(tmp_name);
		free(tmp_name);
	}
	tmp[i] = ft_strjoin("declare -x ", str);
	free(str);
	return (tmp);
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
		while (++j< len)
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

void	sort_and_print_env(t_env *env)
{
	char	**tmp_str;
	int		i;
	int		len;

	len = list_len(env);
	i = 0;
	tmp_str = sort_2D_str(env, len);
	while (i < len)
	{
		if (tmp_str[i] != NULL)
			printf("%s\n", tmp_str[i]);
		i++;
	}
	if (tmp_str != NULL)
		free_2D(tmp_str);

}

void	export(t_env *env, char **str, char **envp)
{
	//int		i;
//char	**tmp_envp;
	(void)envp;
	if (str[1] == '\0')
		sort_and_print_env(env);
}
