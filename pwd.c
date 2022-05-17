/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:49:59 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/13 15:49:58 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char *str = getcwd(NULL, 1024);
	// system("whoami");
	// char *s1 = ft_strtrim(str, "/Users/aabdou/Desktop/");
	//free(str);
	return(free(str), str);
}
