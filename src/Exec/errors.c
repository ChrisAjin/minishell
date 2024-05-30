/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:40:48 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/30 18:30:44 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

// perror au lieu de putstr fd ?
int	command_not_found(t_data *minishell, char **paths)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(minishell->cmd->cmd_param[0], 2);
	// close_all
	// close fds
	// free tout
	if (paths)
		free_tab(paths);
	exit(127);
}

int	exec_fail(t_data *minishell, char **paths)
{
	// close_all
	// close fds
	// free tout
	if (paths)
		free_tab(paths);
	ft_putstr_fd("Could not exec command.\n", 2);
	exit(1);
}

void	permission_denied(t_data *minishell)
{
	ft_putstr_fd("Command not found: ", 2);
	// ft_putendl_fd(cmd, 2);
	// close_all
	// close fds
	// free tout
	exit(126);
}

void	no_such_file(t_data *minishell)
{
	char	*err_msg;

	// err_msg = ft_strjoin("No such file or directory: ", path/cmd);
	ft_putendl_fd(err_msg, 2);
	// close_all
	// close fds
	// free tout
	free(err_msg);
	exit(127);
}

void	empty_cmd(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
	{
		ft_putendl_fd("Command not found.", 2);
		close_fds();
		exit(127);
	}
}

void	dup2_error(t_data *minishell)
{
	// close all
	// tout free ?
	// exit(1);
}
