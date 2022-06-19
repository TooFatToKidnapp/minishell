/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:05:41 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:45:34 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "exec.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexer == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	lexer->str = content;
	lexer->i = 0;
	lexer->c = lexer->str[0];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' || lexer->i != ft_strlen(lexer->str))
	{
		lexer->i += 1;
		lexer->c = lexer->str[lexer->i];
	}
}

void	lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n')
		lexer_advance(lexer);
}

t_token	*lexer_var(t_lexer *lexer, char quote)
{
	char	*string;
	char	*trim;

	string = (char *)malloc(sizeof(char) * 1);
	if (string == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	string[0] = '\0';
	lexer_advance(lexer);
	while (lexer->c != quote)
	{
		trim = lexer_char_to_str(lexer);
		string = ft_strjoin_gnl(string, trim);
		free(trim);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	trim = ft_strtrim(string, " ");
	return (free(string), init_token(TOKEN_VAR, trim));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i != ft_strlen(lexer->str))
	{
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_spaces(lexer);
		if (lexer->c == '>')
			return (lexer_red(lexer, '>'));
		else if (lexer->c == '<')
			return (lexer_red(lexer, '<'));
		else if (lexer->c == '\"')
			return (lexer_var(lexer, '\"'));
		else if (lexer->c == '\'')
			return (lexer_str(lexer, '\''));
		else if (lexer->c == '~')
			return (lexer_advance_with_token(lexer
					, init_token(TOKEN_TILDA, lexer_char_to_str(lexer))));
		else
			return (lexer_word(lexer));
	}
	return (NULL);
}
