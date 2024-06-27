/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:39:02 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 19:03:09 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_last_hd(t_data *minishell, char **env)
{
	open_inf_outf(minishell);
	if (minishell->cmd->cmd_param[0] == NULL)
		clean_exit(minishell, env, 0);
	init_fds(minishell);
	if (pipe(minishell->pip) < 0)
		pipe_error(minishell, env);
	ft_putstr_fd(minishell->token->here_doc, minishell->pip[1]);
	if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
		dup2_error(minishell, env);
	if (minishell->outfile > 0)
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	close_all(minishell);
	if (is_builtin(minishell->cmd->cmd_param[0]))
		exec_builtin(minishell, env);
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0)
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

void	exec_hd(t_data *minishell, char **env)
{
	int	new_pip[2];

	open_inf_outf(minishell);
	if (minishell->cmd->cmd_param[0] == NULL)
		clean_exit(minishell, env, 0);
	if (pipe(new_pip) < 0)
		pipe_error(minishell, env);
	if (write_hd(minishell, new_pip))
		clean_exit(minishell, env, 1);
	if (dup2(new_pip[0], STDIN_FILENO) < 0)
		dup2_error(minishell, env);
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all_new(minishell, new_pip);
	do_exec(minishell, env);
}

int	write_hd(t_data *minishell, int *new_pip)
{
	if (ft_putstr_fd(minishell->token->here_doc, new_pip[1]))
		return (1);
	return (0);
}

void	close_all_new(t_data *minishell, int *new_pip)
{
	close(new_pip[1]);
	close(new_pip[0]);
	close_all(minishell);
}

void	do_exec(t_data *minishell, char **env)
{
	if (is_builtin(minishell->cmd->cmd_param[0]))
		exec_builtin(minishell, env);
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0)
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}
