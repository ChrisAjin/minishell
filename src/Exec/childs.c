/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 17:41:55 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(t_data *minishell)
{
	t_token	*temp;

	temp = minishell->token->next;
	while (temp->type != PIPE && temp->type != 0)
	{
		if (temp->type == HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	only_child(t_data *minishell, char **env)
{
	if (is_here_doc(minishell))
		exec_last_hd(minishell, env);
	open_files(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all(minishell);
	if (minishell->cmd->cmd_param[0] == NULL)
		clean_exit(minishell, env, 0);
	do_exec(minishell, env);
}

void	first_child(t_data *minishell, char **env)
{
	if (is_here_doc(minishell))
		exec_hd(minishell, env);
	open_files(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
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
	close_all(minishell);
	if (minishell->cmd->cmd_param[0] == NULL)
		clean_exit(minishell, env, 0);
	do_exec(minishell, env);
}

void	middle_child(t_data *minishell, char **env)
{
	if (is_here_doc(minishell))
		exec_hd(minishell, env);
	open_files(minishell);
	middle_dup2(minishell, env);
	close_all(minishell);
	if (minishell->cmd->skip_cmd == true)
		clean_exit(minishell, env, 0);
	do_exec(minishell, env);
}

void	last_child(t_data *minishell, char **env)
{
	if (is_here_doc(minishell))
		exec_last_hd(minishell, env);
	open_files(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all(minishell);
	if (minishell->cmd->skip_cmd == true)
		clean_exit(minishell, env, 0);
	do_exec(minishell, env);
}
