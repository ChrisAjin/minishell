/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:40:48 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 18:43:16 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(t_data *minishell, char **paths, char **env)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(minishell->cmd->cmd_param[0], 2);
	close_all(minishell);
	close_fds();
	free_all(minishell, NULL, -1);
	if (paths)
		free_tab(paths);
	if (env)
		free(env);
	exit(127);
}

void	permission_denied(t_data *minishell, char **env)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(minishell->cmd->cmd_param[0], 2);
	close_all(minishell);
	close_fds();
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
	exit(126);
}

void	no_such_file(t_data *minishell, char **env)
{
	ft_putstr_fd("No such file or directory:", 2);
	ft_putendl_fd(minishell->cmd->cmd_param[0], 2);
	close_all(minishell);
	close_fds();
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
	exit(127);
}

void	cur_error(char **paths)
{
	free(paths);
	ft_putendl_fd("malloc error find and exec", 2);
}
