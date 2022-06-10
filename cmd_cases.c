/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skinnyleg <skinnyleg@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:09:03 by skinnyleg         #+#    #+#             */
/*   Updated: 2022/06/07 22:18:07 by skinnyleg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_here_doc_write(t_args *commandes, int index, int *fd_in)
{
	char	*line;
	int		j;

	line = get_next_line(0);
	while (ft_limiter(line, commandes[index].limiter,
			ft_strlen(commandes[index].limiter) + 2))
	{
		j = 0;
		while (line[j] != '\0')
		{
			write(*fd_in, &line[j], 1);
			j++;
		}
		free(line);
		line = get_next_line(0);
	}
	free(line);
}

void	ft_here_doc(t_args *commandes, int index, int *fd_in)
{
	if (commandes[index].here_doc != 0)
	{
		close(*fd_in);
		*fd_in = open("tmp", O_RDWR | O_CREAT, 0645);
		if (*fd_in == -1)
		{
			write(1, "can't open\n", 11);
			exit(1);
		}
		ft_here_doc_write(commandes, index, fd_in);
		close(*fd_in);
		*fd_in = open("tmp", O_RDWR | O_CREAT, 0645);
	}
}

void	ft_if_infile(t_args *commandes, int index, int *fd_in, t_all *var)
{
	if (commandes[index].infile != 0)
	{
		close(*fd_in);
		*fd_in = open(commandes[index].in_file, O_RDONLY);
		if (*fd_in == -1)
		{
			write(1, "can't open\n", 11);
			exit(1);
		}
	}
	else if (index != 0)
	{
		close(*fd_in);
		*fd_in = dup(var->p[index - 1][0]);
	}
}

void	ft_if_outfile(t_args *commandes, int index, int *fd_out, t_all *var)
{
	close(*fd_out);
	if (commandes[index].outappend != 0)
	{
		*fd_out = open(commandes[index].out_append,
				O_RDWR | O_CREAT | O_APPEND, 0645);
		if (*fd_out == -1)
		{
			write(1, "can't open\n", 11);
			exit(1);
		}
	}
	else if (commandes[index].outfile != 0)
	{
		*fd_out = open(commandes[index].out_file,
				O_RDWR | O_CREAT | O_TRUNC, 0645);
		if (*fd_out == -1)
		{
			write(1, "can't open\n", 11);
			exit(1);
		}
	}
	else if (index != var->fork_num - 1)
		*fd_out = dup(var->p[index][1]);
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
