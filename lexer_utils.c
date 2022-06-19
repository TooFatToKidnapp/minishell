/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:21:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/17 23:23:54 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer_str(t_lexer *lexer, char quote)
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
	return (free(string), init_token(TOKEN_STR, trim));
}

t_token	*lexer_red(t_lexer *lexer, char quote)
{
	char	*string;
	char	*str;
	int		i;
	t_token	*token;

	i = 2;
	string = (char *)malloc(sizeof(char) * 1);
	if (string == NULL)
		return (printf("malloc error\n"), exit(1), NULL);
	string[0] = '\0';
	while (lexer->c == quote && i-- != 0)
	{
		str = lexer_char_to_str(lexer);
		if (str == NULL)
			return (free(string), NULL);
		string = ft_strjoin_gnl(string, str);
		free(str);
		lexer_advance(lexer);
	}
	token = get_token(string);
	return (token);
}

int	ft_lexer_if(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->c != '<' && lexer->c != '>'
		&& lexer->c != '\'' && lexer->c != '\"'
		&& lexer->c != '|' && lexer->c != ' ')
		return (1);
	else
		return (0);
}

t_token	*lexer_word(t_lexer *lexer)
{
	char	*string;
	char	*trim;
	char	*str;

	string = (char *)malloc(sizeof(char) * 1);
	if (string == NULL)
		return (printf("malloc error\n"), exit(1), NULL);
	string[0] = '\0';
	if (ft_lexer_if(lexer) == 0)
		return (free(string), NULL);
	while (ft_lexer_if(lexer) == 1)
	{
		str = lexer_char_to_str(lexer);
		if (str == NULL)
			return (free(string), NULL);
		string = ft_strjoin_gnl(string, str);
		free(str);
		lexer_advance(lexer);
	}
	trim = ft_strtrim(string, " ");
	return (free(string), init_token(TOKEN_WORD, trim));
}

char	*lexer_char_to_str(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
