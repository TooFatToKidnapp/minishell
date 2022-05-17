/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:00:59 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/17 19:10:22 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_directions(void) // needs free str
{
	int		i;
	int		red_count;
	int		start;
	char	*str;

	i = 0;
	str = ft_strdup(var.user_input);
	if(check_syntax_right() == 0)
		return (0);
	// while (str[i] != '\0')
	// {
	// 	red_count = 0;
	// 	start = i;
	// 	i = skip_quote(str, i);
	// 	while (str[i] != '\0' && (str[i] == '>' || str[i] == '<'))
	// 	{
	// 		red_count++;
	// 		i++;
	// 	}
	// 	if (start != i && check_directions_Err(str, start, red_count) == 0)
	// 		return (0);
	// 	i++;
	// }
	return (1);
}

int	check_syntax_right(void)   ///   checks for the following conditions " > > , > < , < < , < >" && ignores the redirections inside "" and ''
{
	int		i;
	char	*str;

	str = ft_strdup(var.user_input);
	i = 0;
	while (str[i] != '\0' && str[i] != '>' && str[i] != '\"' && str[i] != '\'')
		i++;
	i = skip_quote(str, i); // ignore whatever is inside quotes
	if (str[i] != '\0')
	{
		i++;
		if (str[i] != '\0' && str[i] == '>')
			i++;
		while (str[i] != '\0' && str[i] == ' ')
			i++;
		if (str[i] != '\0' && str[i] == '>')
			return(printf("minishell: syntax error unexpected token `>'\n"), free(str), 0);
		else if (str[i] != '\0' && str[i] == '<')
			return (printf("minishell: syntax error unexpected token `<'\n"), free(str), 0);
	}
	if (check_syntax_left() == 0)
		return (free(str), 0);
	free(str);
	return (1);
}

int	check_syntax_left(void)
{
	int		i;
	char	*str;

	str = ft_strdup(var.user_input);
	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '\"' && str[i] != '\'')
		i++;
	i = skip_quote(str, i);
	if (str[i] != '\0')
	{
		i++;
		if (str[i] != '\0' && str[i] == '<')
			i++;
		while (str[i] != '\0' && str[i] == ' ')
			i++;
		if (str[i] != '\0' && str[i] == '>' )
			return(printf("minishell: syntax error unexpected token `>'\n"), free(str), 0);
		else if (str[i] != '\0' && str[i] == '<')
			return (printf("minishell: syntax error unexpected token `<'\n"), free(str), 0);
	}
	free(str);
	return (1);
}

int	skip_quote(char *str, int i)
{
	if (str[i] != '\0' && str[i] == '\'')
	{
		i++;
		while(str[i] != '\'')
			i++;
	}
	else if (str[i] != '\0' && str[i] == '\"')
	{
		i++;
		while (str[i] != '\0' && str[i] == '\"')
			i++;
	}
	return (i);
}
