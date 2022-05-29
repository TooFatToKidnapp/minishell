/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdou <aabdou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:01:03 by aabdou            #+#    #+#             */
/*   Updated: 2022/05/29 14:35:55 by aabdou           ###   ########.fr       */
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
	int				index;
	char			**arg;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

struct	s_shell
{
	char	*user_input;
	int		exit_code;

}			var;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;


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

char	**trim_str(char **tab);
int		check_red_pos(char **str);
void	free_list(t_node **node);
////
t_env	*get_env(char **envp);
char	*get_name(char *str);
char	*get_value(char *str);
void	add_var(t_env **env, char *str);

////

////cd/////
char	*get_full_path(char *str, char *home);
char	*get_home(t_env *env);
void	change_dir(char **str, int *i, t_env *env);
void	cd(char **arg, t_env *env);
void	create_or_change_env(t_env *env, char *name, char *value, int len);
////////
t_node	*create_and_fill(char *cmd, int index);
t_node	*add_node_back(t_node *node);
void	add_node(t_node **node, t_node *new);
void	fill_node(char **str, t_node **node);

t_node	**parser(t_node **node);
t_node	**check_err(void);
void	free_2D(char **str);
void	free_env(t_env *env);





void	printBRUH(t_env *env);

#endif
