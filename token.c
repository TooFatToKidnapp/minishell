/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:21:25 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/17 18:37:32 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	token->e_type = type;
	token->value = ft_strdup(value);
	free(value);
	return (token);
}

t_token	*get_token(char *string)
{
	if (!ft_strncmp(string, "<", 2))
		return (init_token(TOKEN_INPUT, string));
	else if (!ft_strncmp(string, "<<", 3))
		return (init_token(TOKEN_HERE_DOC, string));
	else if (!ft_strncmp(string, ">", 2))
		return (init_token(TOKEN_OUTPUT, string));
	else if (!ft_strncmp(string, ">>", 3))
		return (init_token(TOKEN_APPEND, string));
	return (NULL);
}
