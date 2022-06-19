/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:51:15 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/17 18:35:52 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_args	*init_args(void)
{
	t_args	*commands;

	commands = (t_args *)malloc(sizeof(t_args) * 1);
	if (commands == NULL)
	{
		printf("no more space\n");
		exit(1);
	}
	commands->here_doc = 0;
	commands->infile = 0;
	commands->outappend = 0;
	commands->outfile = 0;
	commands->limiter = NULL;
	commands->in_file = NULL;
	commands->out_append = NULL;
	commands->out_file = NULL;
	commands->cmd = NULL;
	return (commands);
}
