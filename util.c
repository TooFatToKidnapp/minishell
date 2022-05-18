/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:22:28 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/18 17:41:07 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**trim_str(char **tab)
{
	char	**str;
	int		i;

	i = 0;
	while (tab[i] != '\0')
		i++;
	str = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i] != '\0')
	{
		str[i] = ft_strtrim(tab[i], " ");
		i++;
	}
	str[i] = NULL;
	return (str);
}
