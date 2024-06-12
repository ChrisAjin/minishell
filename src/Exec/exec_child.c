/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:34:23 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/12 13:05:36 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// comment faire si redir avec parent builtin :(
int	one_cmd(t_data *minishell, char **env)
{
	int	pid;

	// parent_builtin(minishell, env);
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
		only_child(minishell, env);
	wait_and_error(minishell, pid);
	return (0);
}

int	exec_first_child(t_data *minishell, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
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
	last_child(minishell, env);
	wait_and_error(minishell, pid);
	return (0);
}
