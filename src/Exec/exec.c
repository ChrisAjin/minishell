/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/14 17:58:04 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ajouter un skip cmd pour faciliter le empty cmd check?
// !!! penser a free char **env partout (ajouter a free all?)
int	exec(t_data *minishell)
{
	char	**env;

	minishell->pipes = pipe_count(minishell);
	env = list_to_arr(minishell->env);
	if (minishell->pipes == 0)
	{
		if (one_cmd(minishell, env) < 0)
			return (child_fail(minishell, env));
		free(env);
		close_all(minishell);
		return (0);
	}
	else if (minishell->pipes >= 1)
	{
		if (exec_first_child(minishell, env) < 0)
			return (child_fail(minishell, env));
		skip(&minishell); // pipes - 1 dans skip
		while (minishell->pipes != 0) // (while pas sur la derniere cmd)
		{
			if (exec_middle_childs(minishell, env) < 0)
				return (child_fail(minishell, env));
			skip(&minishell);
		}
		if (minishell->temp_fd > 0)
			close(minishell->temp_fd);
	}
	if (exec_last_child(minishell, env) < 0)
		return (child_fail(minishell, env));
	free(env);
	return (0);
}

// pour commande sans path
void	find_and_exec(t_data *minishell, char **env)
{
	int		i;
	char	**paths;
	char	*cur_path;
	char	*temp;

	i = 0;
	paths = split_path(env);
	while (paths != NULL && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cur_path = ft_strjoin(temp, minishell->cmd->cmd_param[0]);
		free(temp);
		if (!cur_path)
		{
			free(paths);
			ft_putendl_fd(ERR_MALLOC, 2);
			return ;
		}
		if (access(cur_path, F_OK | X_OK) >= 0)
			if (execve(cur_path, minishell->cmd->cmd_param, env) < 0)
				exec_fail(minishell, paths, env);
		free(cur_path);
		i++;
	}
	command_not_found(minishell, paths, env);
}

// pour commande avec path
void	exec_path(t_data *minishell, char **env)
{
	if (access(minishell->cmd->cmd_param[0], F_OK | X_OK) == 0)
		if (execve(minishell->cmd->cmd_param[0], minishell->cmd->cmd_param,
				env) < 0)
			exec_fail(minishell, NULL, env);
	if (access(minishell->cmd->cmd_param[0], F_OK) < 0)
		no_such_file(minishell, env);
	permission_denied(minishell, env);
}

int	pipe_count(t_data *minishell)
{
	int		pipes;
	t_token	*tmp;

	pipes = 0;
	tmp = minishell->token;
	tmp = tmp->next; // pcq le premier ne peut pas etre un pipe (unexpected token)
	while (tmp != minishell->token)
	{
		if (tmp->type == PIPE)
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}
