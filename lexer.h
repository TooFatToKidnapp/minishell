/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:40:18 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:39:05 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include <stdlib.h>

typedef struct lexer_struct
{
	char			*str;
	unsigned int	i;
	char			c;
}	t_lexer;

t_lexer	*init_lexer(char *content);

void	lexer_advance(t_lexer *lexer);

void	lexer_skip_spaces(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer *lexer);

t_token	*lexer_str(t_lexer *lexer, char quote);

char	*lexer_char_to_str(t_lexer *lexer);

t_token	*lexer_red(t_lexer *lexer, char quote);

t_token	*lexer_word(t_lexer *lexer);

t_token	*get_token(char *string);

t_token	*lexer_var(t_lexer *lexer, char quote);

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);
#endif
