/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:14:48 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/17 17:36:15 by aabdou           ###   ########.fr       */
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
		return (printf("Minishell: syntax error\n"), free(str), 0);
	free (str);
	return (1);
}

///////////////
//i = 30 ; j = 31
int	check_directions_Err(char *str, int i, int j)
{
	char	*tmp;

	if (j > 0)
	{
		tmp = ft_substr(str, i ,j);
		if (redirect(tmp, j) == 0)
		{
			redirect_Err(tmp);
			free(tmp);
			return 0;
		}
		free(tmp);
	}
	return (1);
}

int	redirect(char *str, int i)
{
	if (ft_strncmp(str, ">", i) == 0 || ft_strncmp(str, "<<", i) == 0
		|| ft_strncmp(str, ">>", i) == 0
		|| ft_strncmp(str, "<", i) == 0)
		return (1);
	else
		return (0);
}

int	redirect_Err(char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i] != '\0')
	{
		count = 0;
		while (str[i] != '\0' && str[i] == '>')
		{
			count++;
			i++;
		}
		if (count > 2)
			return (printf("Minishell: syntax error near unexpected token `>>'\n"), 0);
		count = 0;
		while (str[i] != '\0' && str[i] == '<')
		{
			count++;
			i++;
		}
		if (count > 2)
			return (printf("Minishell: syntax error near unexpected token `<<'\n"), 0);
		i++;
	}
	return (1);
}
