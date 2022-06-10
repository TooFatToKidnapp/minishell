/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:14:48 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/09 19:12:52 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(void)
{
	int		i;
	int		s_q;
	int		d_q;
	char	*str;

	i = 0;
	s_q = 0;
	d_q = 0;
	str = ft_strdup(var.user_input);
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && d_q == 0 && s_q == 0)
			d_q = 1;
		else if (str[i] == '\"' && d_q == 1 && s_q == 0)
			d_q = 0;
		else if (str[i] == '\'' && d_q == 0 && s_q == 0)
			s_q = 1;
		else if (str[i] == '\'' && d_q == 0 && s_q == 1)
			s_q = 0;
		i++;
	}
	if (s_q == 1 || d_q == 1)
		return (printf("Minishell: syntax error\n"),
			var.exit_code = 258, free(str), 0);
	return (free (str), 1);
}
