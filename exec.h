/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/18 17:47:59 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "token.h"
# include "lexer.h"
# include <sys/wait.h>
# include "libft/libft.h"
# include "minishell.h"
# include "GNL/get_next_line.h"

typedef struct s_all{
	char	*paths;
	char	*cmd_path;
	int		i;
	int		j;
	int		fd[2];
	int		**p;
	pid_t	pid;
	int		fork_num;
	int		pipe_num;
	t_node	*node;
	char	**built_envp;

}	t_all;

typedef struct s_args{
	int		infile;
	char	*in_file;
	int		outfile;
	char	*out_file;
	int		outappend;
	char	*out_append;
	int		here_doc;
	char	*limiter;
	char	**cmd;
}	t_args;

typedef struct s_lists{
	int				type;
	char			*value;
	struct s_lists	*next;
	struct s_lists	*prev;
}	t_lists;

void	free_memory_pipex(char **s);
char	*ft_strjoin_pipex(char const *s1,	char const *s2);
void	ft_path_checker(char *paths);
void	ft_path_null(char *path);
char	*ft_path(char *env, char *av);
char	*ft_findpath(t_env *env);
void	ft_malloc(void *tab);
int		ft_init(t_all *var, t_node *node, char **envp);
int		ft_init2(t_all *var);
int		ft_routine(t_all *var, t_args *args, t_env *env, int index);
int		lst_size(t_node *node);
t_args	*init_args(void);
void	free_var(t_all *var);
int		ft_limiter(char *line, char *limiter, int size);
void	create_env2(t_env *env, char **envp);
int		ft_if_outfile(t_args *commandes, int index, int *fd_out, t_all *var);
int		ft_if_infile(t_args *commandes, int index, int *fd_in, t_all *var);
int		ft_here_doc(t_args *commandes, int *fd_in);
void	close_all(t_all *var, int fd_in, int fd_out);
int		ft_part2(int *fd_in, t_args *args);
int		ft_here_doc_write(t_args *args, int *fd_in);
void	free_block(t_lists **list, char *str);
t_args	*list_cmd(t_lists *list, t_args *argum);
void	free_myargs(t_args **args);
void	add_back(t_lists **head, t_lists *new);
void	free_mylist(t_lists **list);
char	**create_env(t_env *env);
void	ft_close_free(t_all *vars, char **input);
int		check_if(t_all *vars, t_node *node, char **envp);
int		ft_while(t_lists **list, t_args **argum, t_lists **prev);
int		builtins_check(t_args *args, t_env **env, t_all *vars);
void	ft_malloc_exit(void *tab);
void	exec_builtins(t_args *args, int index, t_all *vars, t_env **env);
void	*exec_cmd(t_args *args, int index, t_env *env, t_all *vars);
void	execute(t_all *vars, t_args *args, t_env **env, int index);
void	expansion(t_lists **head, t_env *env);
void	free_empty(t_lists **list);
int		int_strchr(const char *s, int c);
#endif
