/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:00:27 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/07 23:21:57 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_to_envp(char **tmp_envp, char **envp)
{
	int	i;

	i = 0;
	while (tmp_envp[i])
	{
		if (!envp[i])
			envp[i] = ft_strdup(tmp_envp[i]);
		else
			ft_strlcpy(envp[i], tmp_envp[i], ft_strlen(tmp_envp[i]) + 1);
		i++;
	}
	envp[i] = NULL;
	free_2D(tmp_envp);
}

char	**fill_tmp_envp(t_env *env)
{
	char	*tmp_name;
	char	**tmp_envp;
	int		i;

	i = 0;
	tmp_envp = malloc(sizeof(char *) * list_len(env) + 1);
	if (tmp_envp == NULL)
		exit(EXIT_FAILURE);
	while (env != NULL)
	{
		tmp_name = ft_strjoin(env->name, "=");
		if (env->value)
			tmp_envp[i] = ft_strjoin(tmp_name, env->value);
		else
			tmp_envp[i] = ft_strdup(tmp_name);
		free(tmp_name);
		if (env->next)
		{
			i++;
			env = env->next;
		}
		else
			break ;
	}
	tmp_envp[i + 1] = NULL;
	return (tmp_envp);
}

int check_and_change(char *str, t_env *env)
{
	if (str[0] == '=' || ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "\'\'") == 0)
	{
		if (ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "\'\'") == 0)
			str = ft_strdup("");
		printf("export: `%s': not a valid identifier\n", str);
		return (1);
	}
	else
		ft_add_to_env(env, str, 0, 0);
	return (0);
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
		if (tmp_str[i][0] != '\0')
			printf("%s\n", tmp_str[i]);
		i++;
	}
	if (tmp_str != NULL)
		free_2D(tmp_str);
}

void	export(t_env *env, char **str, char **envp)
{
	int		i;
	char	**tmp_envp;

	i = 0;
	if (str[1] == NULL || str[1][0] == '#')
		sort_and_print_env(env);
	else
	{
		while (str[++i])
		{
			if (check_and_change(str[i], env))
				return;
		}
		tmp_envp = fill_tmp_envp(env);
		copy_to_envp(tmp_envp, envp);
	}
 }
