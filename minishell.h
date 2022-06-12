/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:01:03 by aabdou            #+#    #+#             */
/*   Updated: 2022/06/12 19:20:12 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <paths.h>

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
	int		forks;
	int		exit_code;

}			var;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

char	*get_prompt(void);
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
t_env	*get_env(char **envp, int flag);
char	*get_name(char *str);
char	*get_value(char *str);
void	add_var(t_env **env, char *str);
char	*get_full_path(char *str, char *home);
char	*get_home(t_env *env);
void	change_dir(char **str, int *i, t_env *env);
void	cd(char **arg, t_env *env);
void	*create_or_change_env(t_env *env, char *name, char *value, int len);
void	pwd(void);
void	echo(char **str);
int		ft_checkflag(char *str);
void	export(t_env **env, char **str, char **envp);
void	sort_and_print_env(t_env *env);
char	**sort_2d_str(t_env *node, int len);
char	**fill_2d(t_env *node, int len);
char	**fill_block_in_2d(t_env *node, int i, char **tmp);
int		list_len(t_env *node);
int		ft_add_to_env(t_env **env, char *str, int i, int equal_pos);
void	*update_env(t_env **env, char *name, char *value);
void	new_env(char *name, char *value, t_env **env);
int		check_identifier(char *str);
void	allocate(char **name, char **value, char *str, int pos);
int		get_equal_pos(char *str);
int		check_and_change(char *str, t_env **env);
char	**fill_tmp_envp(t_env *env, int i);
void	copy_to_envp(char **tmp_envp, char **envp);
void	print_env(t_env *env);
t_env	*create_path_pwd(void);
void	unset(t_env **env, char **cmd, char **envp);
int		check_if_valid(char *var);
t_env	ft_delete_env(t_env *env, t_env *tmp, char *tmp_cmd, char **envp);
void	update_envp(t_env *env, char **envp);
char	**new_envp(t_env *env);
t_env	*remove_last_env(t_env **env, char *tmp_cmd);
void	remove_env(char *name, t_env **env, char **envp);
t_node	*create_and_fill(char *cmd, int index);
t_node	*add_node_back(t_node *node);
void	add_node(t_node **node, t_node *new);
void	fill_node(char **str, t_node **node);
t_node	**parser(t_node **node, t_env *env);
t_node	**check_err(t_env *env);
void	free_2d(char **str);
void	free_env(t_env **env);
void	pipex(t_node *node, t_env *env);
void	exit_shell(char **str, int i);
void	check_dollar(char **str, t_env *env);
int		ft_dollar_only(char *dollar);
int		ft_switch(t_env *env, char **dollar, char **str);
char	*ft_dollar(char **dollar);
#endif
