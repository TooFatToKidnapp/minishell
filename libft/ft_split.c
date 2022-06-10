/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:45:53 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/09 19:08:03 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_count(char const *s, char c, int i, int word)
{
	while (s[i])
	{
		if (s[i] != c)
		{
			if (s[i] == '\"')
			{
				i++;
				while (s[i] != '\"')
					i++;
			}
			if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					i++;
			}
			if (s[i + 1] == c || s[i + 1] == '\0')
				word++;
		}
		i++;
	}
	return (word);
}

int	get_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	**fill(const char *s, char c, int word, char **splitted)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < word)
	{
		while (*s == c)
			s++;
		len = get_len(s, c);
		splitted[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!splitted[i])
			return (perror("Error"), exit (EXIT_FAILURE), NULL);
		j = 0;
		while (j < len)
		{
			splitted[i][j++] = *s++;
		}
		splitted[i][j] = '\0';
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	word = get_count(s, c, 0, 0);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!tab)
	{
		while (tab[i++])
		{
			free(tab[i]);
		}
		free(tab);
		return (perror("Error, split"), exit(EXIT_FAILURE), NULL);
	}
	tab = fill(s, c, word, tab);
	return (tab);
}
