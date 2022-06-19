/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:09:03 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/18 17:48:19 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_here_doc_write(t_args *args, int *fd_in)
{
	char	*line;
	int		j;

	line = get_next_line(0);
	if (line == NULL)
		return (0);
	while (var.ctrl_c == 0 && ft_limiter(line, args->limiter,
			ft_strlen(args->limiter) + 2))
	{
		j = 0;
		while (line[j] != '\0')
		{
			write(*fd_in, &line[j], 1);
			j++;
		}
		free(line);
		line = get_next_line(0);
		if (line == NULL)
			return (0);
	}
	free(line);
	if (var.ctrl_c != 0)
		return (1);
	return (0);
}

int	ft_here_doc(t_args *args, int *fd_in)
{
	if (args->in_file == NULL && args->limiter != NULL)
	{
		*fd_in = open("tmp", O_RDWR);
		if (*fd_in == -1)
		{
			write(1, "can't open\n", 11);
			return (1);
		}
	}
	return (0);
}

int	ft_if_infile(t_args *args, int index, int *fd_in, t_all *var)
{
	if (args->in_file != NULL)
	{
		close(*fd_in);
		*fd_in = open(args->in_file, O_RDONLY);
		if (*fd_in == -1)
		{
			write(1, "can't open\n", 11);
			return (1);
		}
	}
	else if (index != 0 && args->limiter == NULL)
	{
		close(*fd_in);
		*fd_in = dup(var->p[index - 1][0]);
	}
	return (0);
}

int	ft_if_outfile(t_args *args, int index, int *fd_out, t_all *var)
{
	close(*fd_out);
	if (args->out_append != NULL)
	{
		*fd_out = open(args->out_append,
				O_RDWR | O_CREAT | O_APPEND, 0645);
		if (*fd_out == -1)
		{
			write(1, "can't open\n", 11);
			return (1);
		}
	}
	else if (args->out_file != NULL)
	{
		*fd_out = open(args->out_file,
				O_RDWR | O_CREAT | O_TRUNC, 0645);
		if (*fd_out == -1)
		{
			write(1, "can't open\n", 11);
			return (1);
		}
	}
	else if (index != var->fork_num - 1)
		*fd_out = dup(var->p[index][1]);
	return (0);
}

void	close_all(t_all *var, int fd_in, int fd_out)
{
	int	j;

	j = 0;
	while (j < var->pipe_num)
	{
		close(var->p[j][0]);
		close(var->p[j][1]);
		j++;
	}
	close(fd_out);
	close(fd_in);
}
