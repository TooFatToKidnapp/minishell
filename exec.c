/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/06/19 15:15:13 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute(t_all *vars, t_args *args, t_env **env, int index)
{
	if (check(args->cmd[0]) == 1)
		exec_builtins(args, index, vars, env);
	else
	{
		vars->pid = fork();
		var.forks++;
		if (vars->pid == -1)
		{
			printf("ERROR3\n");
			return ;
		}
		if (vars->pid == 0)
			exec_cmd(args, index, *env, vars);
	}
	if (index < vars->pipe_num)
		close(vars->p[index][1]);
}

t_lists	*init_list(t_token *token)
{
	t_lists	*list;

	list = (t_lists *)malloc(sizeof(t_lists) * 1);
	if (list == NULL)
	{
		printf("list error\n");
		exit(1);
	}
	list->type = token->e_type;
	list->value = ft_strdup(token->value);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

t_lists	*fill_mylist(char *input, t_env *env)
{
	t_lexer	*lexer;
	t_token	*token;
	t_lists	*list;
	t_lists	*head;

	head = NULL;
	lexer = init_lexer(input);
	if (lexer == NULL)
		return (NULL);
	token = lexer_get_next_token(lexer);
	while (token != NULL)
	{
		list = init_list(token);
		free(token->value);
		free(token);
		if (list == NULL)
			return (printf("list error\n"), NULL);
		add_back(&head, list);
		token = lexer_get_next_token(lexer);
	}
	expansion(&head, env);
	return (free(lexer), head);
}

t_args	*fill_myargs(t_lists **list)
{
	t_args	*argum;
	t_lists	*prev;

	prev = NULL;
	argum = init_args();
	if (argum == NULL)
		return (NULL);
	if (ft_while(list, &argum, &prev) == -1)
		return (NULL);
	(*list) = prev;
	if (*list != NULL)
	{
		while ((*list)->prev != NULL)
			*list = (*list)->prev;
	}
	argum = list_cmd(*list, argum);
	if (argum == NULL)
		return (NULL);
	return (argum);
}

void	exec(t_node *node, t_env **env, char **envp)
{
	t_lists	*list;
	t_all	vars;
	t_args	*args;
	char	**input;
	int		i;

	i = -1;
	if (check_if(&vars, node, envp) == 1)
		return ;
	input = ft_split(var.user_input, '|');
	vars.i = vars.fork_num;
	while (input[++i])
	{
		list = fill_mylist(input[i], *env);
		if (list == NULL)
			continue ;
		args = fill_myargs(&list);
		if (args == NULL)
			continue ;
		free_mylist(&list);
		execute(&vars, args, env, i);
		free_myargs(&args);
	}
	ft_close_free(&vars, input);
}
