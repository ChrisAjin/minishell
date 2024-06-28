/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:34:23 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/28 16:00:31 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_one_cmd(t_data *minishell, char **env)
{
	if (one_cmd(minishell, env) < 0)
		return (child_fail(minishell, env));
	return (0);
}

int	one_cmd(t_data *minishell, char **env)
{
	if (is_parent_builtin(minishell->cmd->cmd_param[0]))
		return (parent_builtin(minishell, env));
	minishell->pid = fork();
	if (minishell->pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (minishell->pid == 0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		only_child(minishell, env);
	}
	wait_and_error(minishell, minishell->pid);
	close_all(minishell);
	if (env)
		free(env);
	return (0);
}

int	exec_first_child(t_data *minishell, char **env)
{
	if (pipe(minishell->pip) < 0)
	{
		perror("pipe error");
		return (-1);
	}
	minishell->pid = fork();
	if (minishell->pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (minishell->pid == 0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		first_child(minishell, env);
	}

	return (0);
}

int	exec_middle_childs(t_data *minishell, char **env)
{
	if (renew_pipe(minishell) < 0)
		return (-1);
	minishell->pid = fork();
	if (minishell->pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (minishell->pid == 0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		middle_child(minishell, env);
	}
	return (0);
}

int	exec_last_child(t_data *minishell, char **env)
{
	minishell->pid = fork();
	if (minishell->pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (minishell->pid == 0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		last_child(minishell, env);
	}

	close_all(minishell);
	wait_and_error(minishell, minishell->pid);
	return (0);
}
