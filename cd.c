/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:30:41 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/27 20:17:37 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_full_path(char *str, char *home)
{
	char	*dir;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (str[i] != '\0')
		i++;
	dir = malloc(sizeof(char ) * (ft_strlen(home) + i));
	if (dir == NULL)
		return (perror("Error malloc"), exit(EXIT_FAILURE), NULL);
	if (home != NULL)
		ft_strlcpy(dir, home, ft_strlen(home) + 1);
	i = 0;
	while (dir[i])
		i++;
	while (str[j])
	{
		dir[i] = str[j];
		i++;
		j++;
	}
	dir[i] = '\0';
	return (dir);
}

char	*get_home(t_env *env)
{
	while(env != NULL)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


int	change_dir(char **str, int i, t_env *env)
{
	char	*home;
	char	*dir;

	home = get_home(env);
	if (str[1] != NULL && str[1][0] == '~')
	{
		dir = get_full_path(str[1], home);
		i = chdir(dir);
		free(dir);
	}
	else if (str[1] != NULL && str[1][0] != '~')
		i = chdir(str[1]);
	else if (str[1])
	{
		if (home)
			i = chdir(home);
		else
			printf("Minishell : Error can't find HOME\n");
	}
	return (i);
}

void	cd(char **arg, t_env *env)
{
	int		i;
	char	current_dir[1024];
	//char	new_dir[1024];

	i = 0;
	getcwd(current_dir, 1024);
	i = change_dir(arg, i , env);
	if (i == -1)
		printf("cd : %s no such file in directory\n", arg[1]);
	// else if (env == NULL)
	// {
	// 	getcwd(new_dir, 1024);
	// 	change_dir()
	// }

}
