/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:40:48 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 14:34:15 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_not_found(t_data *minishell, char **paths)
{
	ft_putstr_fd("Command not found: ", 2);
	// ft_putendl_fd(cmd, 2);
	close_all(minishell);
	close_fds();
	// free tout
	if (paths)
		free_tab(paths);
	exit(127);
}

int	exec_fail(t_data *minishell, char **paths)
{
	close_all(minishell);
	close_fds();
	// free tout
	if (paths)
		free_tab(paths);
	ft_putstr_fd("Could not exec command.\n", 2); // voir si modifier msg
	exit(1);
}

void	permission_denied(t_data *minishell)
{
	ft_putstr_fd("Command not found: ", 2);
	// ft_putendl_fd(cmd, 2);
	close_all(minishell);
	close_fds();
	// free tout
	exit(126);
}

void	no_such_file(t_data *minishell)
{
	ft_putstr_fd("No such file or directory: ", 2);
	// ft_putendl_fd(path/cmd, 2);
	close_all(minishell);
	close_fds();
	// free tout
	exit(127);
}

// void	empty_cmd(void)
// {
// 	if (!minishell->cmd->cmd_param || minishell->cmd->cmd_param[0] == '\0')
// 	{
// 		ft_putendl_fd("Command not found.", 2);
// 		close_fds();
// 		exit(127);
// 	}
// }

void	dup2_error(t_data *minishell)
{
	// perror("dup2 error"); a voir si on met un msg ou pas
	close_all(minishell);
	close_fds();
	// tout free
	exit(1);
}
