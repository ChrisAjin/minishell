/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:20:55 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/28 19:48:39 by inbennou         ###   ########.fr       */
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

void	exec_fail(t_data *minishell, char **paths, char **env, char *cur_path)
{
	close_all(minishell);
	free_all(minishell, NULL, -1);
	if (paths)
		free_tab(paths);
	if (env)
		free(env);
	if (cur_path)
		free(cur_path);
	ft_putstr_fd("Could not exec command.\n", 2);
	close_fds();
	exit(1);
}

void	path_fail(t_data *minishell, char **env)
{
	close_all(minishell);
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
	ft_putendl_fd("is a directory", 2);
	close_fds();
	exit(126);
}

void	dup2_error(t_data *minishell, char **env)
{
	close_all(minishell);
	close_fds();
	free_all(minishell, NULL, -1);
	if (env)
		free(env);
	exit(1);
}

void	pipe_error(t_data *minishell, char **env)
{
	perror("pipe error");
	close_fds();
	close_all(minishell);
	free(env);
	free_all(minishell, NULL, -1);
	exit(1);
}
