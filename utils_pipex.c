/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:55 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/17 23:53:54 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_findpath(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_malloc(void *tab)
{
	if (tab == NULL)
	{
		printf("ERROR4\n");
		exit(1);
	}
}

char	*ft_strjoin_pipex(char const *s1, char const *s2)
{
	size_t	len;
	char	*s3;

	if (!s1)
		return ((char *)s2);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(sizeof(char) * len);
	ft_malloc(s3);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcat(s3, s2, len);
	return (s3);
}

void	ft_path_null(char *path)
{
	if (path == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(1);
	}
}
