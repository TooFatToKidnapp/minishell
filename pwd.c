/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:49:59 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/01 18:04:27 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char str[1024];
	getcwd(str, 1024);
	return(ft_strdup(str));
}

void	pwd(void)
{
	char str[1024];
	getcwd(str, 1024);
	printf("%s\n", str);
}
