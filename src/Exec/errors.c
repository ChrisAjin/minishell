/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:40:48 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/11 19:17:01 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_fail(t_data *minishell, char **env)
{
	minishell->exit_code = 1;
	free(env);
	close_all(minishell);
	return (0);
}

void	command_not_found(t_data *minishell, char **paths, char **env)
{
	ft_putstr_fd("Command not found: ", 2);
	// ft_putendl_fd(cmd, 2);
	close_all(minishell);
	close_fds();
	free_all(minishell, NULL, -1);
	if (paths)
		free_tab(paths);
	if (env)
		free(env);
	exit(127);
}

void	exec_fail(t_data *minishell, char **paths, char **env)
{
	close_all(minishell);
	close_fds();
	// free tout
	free_all(minishell, NULL, -1);
	if (paths)
		free_tab(paths);
	if (env)
		free(env);
	ft_putstr_fd("Could not exec command.\n", 2); // voir si modifier msg
	exit(1);
}

void	permission_denied(t_data *minishell, char **env)
{
	ft_putstr_fd("Command not found: ", 2);
	// ft_putendl_fd(cmd, 2);
	close_all(minishell);
	close_fds();
	// free tout
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
	exit(126);
}

void	no_such_file(t_data *minishell, char **env)
{
	ft_putstr_fd("No such file or directory: ", 2);
	// ft_putendl_fd(path/cmd, 2);
	close_all(minishell);
	close_fds();
	// free tout
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
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

void	dup2_error(t_data *minishell, char **env)
{
	perror("dup2 error"); // a voir si on met un msg ou pas
	close_all(minishell);
	close_fds();
	// tout free
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
	exit(1);
}
