/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:14:50 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 14:30:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "exec.h"

int	first_if(t_args **argum, t_lists **list)
{
	free((*argum)->in_file);
	(*argum)->infile = 1;
	(*argum)->here_doc = 0;
	(*argum)->in_file = ft_strdup((*list)->next->value);
	if ((*argum)->in_file == NULL)
		return (-1);
	free_block(list, (*argum)->in_file);
	free_block(list, "<");
	return (0);
}

int	second_if(t_args **argum, t_lists **list)
{
	int	fd_in;

	free((*argum)->limiter);
	free((*argum)->in_file);
	(*argum)->in_file = NULL;
	(*argum)->limiter = ft_strdup((*list)->next->value);
	if ((*argum)->limiter == NULL)
		return (-1);
	free_block(list, (*argum)->limiter);
	free_block(list, "<<");
	fd_in = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0645);
	if (ft_here_doc_write(*argum, &fd_in) == 1)
		return (close(fd_in), -1);
	close(fd_in);
	return (0);
}

int	third_if(t_args **argum, t_lists **list)
{
	int	fd;

	free((*argum)->out_file);
	(*argum)->out_file = ft_strdup((*list)->next->value);
	if ((*argum)->out_file == NULL)
		return (-1);
	if ((*argum)->out_file != NULL)
	{
		fd = open((*argum)->out_file, O_RDWR | O_CREAT | O_TRUNC, 0645);
		if (fd == -1)
			return (printf("can't open\n"), -1);
		close(fd);
	}
	free_block(list, (*argum)->out_file);
	free_block(list, ">");
	return (0);
}

int	fourth_if(t_args **argum, t_lists **list)
{
	int	fd;

	free((*argum)->out_append);
	(*argum)->out_append = ft_strdup((*list)->next->value);
	if ((*argum)->out_append == NULL)
		return (-1);
	if ((*argum)->out_append != NULL)
	{
		fd = open((*argum)->out_append, O_RDWR | O_CREAT | O_APPEND, 0645);
		if (fd == -1)
			return (printf("can't open\n"), -1);
		close(fd);
	}
	free_block(list, (*argum)->out_append);
	free_block(list, ">>");
	return (0);
}

int	ft_while(t_lists **list, t_args **argum, t_lists **prev)
{
	int	check;

	check = 0;
	while ((*list))
	{
		if ((*list)->type == TOKEN_INPUT)
			check = first_if(argum, list);
		else if ((*list)->type == TOKEN_HERE_DOC)
			check = second_if(argum, list);
		else if ((*list)->type == TOKEN_OUTPUT)
			check = third_if(argum, list);
		else if ((*list)->type == TOKEN_APPEND)
			check = fourth_if(argum, list);
		else if (*list != NULL)
		{
			*prev = (*list);
			*list = (*list)->next;
		}
		if (check == -1)
			return (-1);
	}
	return (0);
}
