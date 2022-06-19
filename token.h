/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:55:21 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:34:36 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct token_struct
{
	enum
	{
		TOKEN_WORD,
		TOKEN_INPUT,
		TOKEN_OUTPUT,
		TOKEN_APPEND,
		TOKEN_HERE_DOC,
		TOKEN_STR,
		TOKEN_VAR,
		TOKEN_TILDA,
	}	e_type;
	char	*value;
}	t_token;

t_token	*init_token(int type, char *value);
#endif
