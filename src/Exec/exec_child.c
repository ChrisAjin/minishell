/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:34:23 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/20 17:15:21 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one_cmd(t_data *minishell, char **env)
{
	if (one_cmd(minishell, env) < 0)
		return (child_fail(minishell, env));
	// if (env != NULL)
	// 	free(env);
	// close_all(minishell);
	return (0);
}

int	one_cmd(t_data *minishell, char **env)
{
	int	pid;

	// if empty
	if (is_parent_builtin(minishell->cmd->cmd_param[0]))
		return (parent_builtin(minishell, env));
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
		only_child(minishell, env);
	wait_and_error(minishell, pid);
	close_all(minishell);
	if (env)
		free(env);
	return (0);
}

int	exec_first_child(t_data *minishell, char **env)
{
	int	pid;

	if (pipe(minishell->pip) < 0)
		perror("pipe error");
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
		first_child(minishell, env);
	return (0);
}

int	exec_middle_childs(t_data *minishell, char **env)
{
	int	pid;

	if (renew_pipe(minishell) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
		middle_child(minishell, env);
	return (0);
}

int	exec_last_child(t_data *minishell, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
		last_child(minishell, env);
	close_all(minishell);
	wait_and_error(minishell, pid);
	return (0);
}
