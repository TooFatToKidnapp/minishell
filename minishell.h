/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:01:03 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/16 23:31:09 by aabdou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <signal.h>
#include <stdbool.h>

typedef struct s_node
{
	char	**args;

}			t_node;

struct	s_shell
{
	char	*user_input;

}			var;

char	*get_prompt();
void	sigint(int sig);
char	*get_pwd(void);
int		check_start_and_end(void);
int		check_pipes_back_to_back(void);
int		check_pipes(void);
int		check_quotes(void);
int		check_syntax_left(void);
int		check_syntax_right(void);
int		check_directions(void);
int		redirect(char *str, int i);
int		redirect_count_err(char *line);
int		redirect_Err(char *str);
int		skip_quote(char *str, int i);
int		check_directions_Err(char *str, int i, int j);

t_node	**parser(t_node **node);
t_node	**check_err(void);
void	free_2D(char **str);

#endif
