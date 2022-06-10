/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/09 17:47:20 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
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
	int		*pid;
	int		fork_num;
	int		pipe_num;

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

void	free_memory_pipex(char **s);
void	ft_file(int fd, char *path, char **cmd);
char	*ft_strjoin_pipex(char const *s1,	char const *s2);
char	**ft_split_pipex(char const *s,	char c);
void	ft_pid(pid_t pid, char *path, char **cmd);
void	ft_path_checker(char *paths);
void	ft_execve_error(char *path, char **cmd, int a);
void	ft_split_check(char **cmd);
void	ft_path_null(char *path);
void	ft_read(int *p, char *path, char **cmd);
char	*ft_path(char *env, char *av);
char	*ft_findpath(t_env *env);
void	ft_malloc(void *tab);
void	ft_init(t_all *var, t_env *env, int ac);
void	ft_init2(t_all *var);
void	ft_routine(t_all *var, t_args *commandes, t_env *env);
void	exec_cmd(t_all *var, t_args *commandes, t_env *env, int index);
int		lst_size(t_node *node);
void	normal_mode(t_args *commands, t_env *env, t_node *node);
char	*ft_findpath_char(char **env);
t_args	*parse_arg(t_node *node);
void	init_cmd(t_node *node, t_args *commands, int size);
void	init_args(t_args *commands, int size);
void	fill_arg(t_args commands, t_node node);
int		ft_while(t_node *node, t_args *commands);
void	free_var(t_all *var);
int		ft_limiter(char *line, char *limiter, int size);
void	free_commands(t_args *commands, int size);
void	normal_mode(t_args *commands, t_env *env, t_node *node);
void	create_env2(t_env *env, char **envp);
void	ft_if_outfile(t_args *commandes, int index, int *fd_out, t_all *var);
void	ft_if_infile(t_args *commandes, int index, int *fd_in, t_all *var);
void	ft_here_doc(t_args *commandes, int index, int *fd_in);
void	close_all(t_all *var, int fd_in, int fd_out);
void	free_inside(t_args commands);
#endif
