/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 19:42:33 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// faire un empty cmd check

// dans le meme child, si l'infile n'existe pas, alors l'outfile n'est pas cree

void	only_child(t_data *minishell, char **env)
{
	// if (minishell->token->type == 2)
		// exec_here_doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
	{
		minishell->outfile = -1;
		free_all(minishell, NULL, -1);
		exit(1);
	}
	else
		open_outfile(minishell, outfile_count(minishell));
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
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
	{
		exec_builtin(minishell, env);
		// free(env);
		// free_all(minishell, NULL, -1);
		// exit(minishell->exit_code);
	}
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

void	first_child(t_data *minishell, char **env)
{
	// if here_doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
	{
		minishell->outfile = -1;
		free_all(minishell, NULL, -1);
		exit(1);
	}
	else
		open_outfile(minishell, outfile_count(minishell));
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
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
	{
		exec_builtin(minishell, env);
		// free(env);
		// free_all(minishell, NULL, -1);
		// exit(minishell->exit_code);
	}
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

// middle child avec temp fd et child_nbr
void	middle_child(t_data *minishell, char **env)
{
	// if here doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
	{
		minishell->outfile = -1;
		free_all(minishell, NULL, -1);
		exit(1);
	}
	else
		open_outfile(minishell, outfile_count(minishell));
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->temp_fd, STDIN_FILENO) < 0)
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
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
	{
		exec_builtin(minishell, env);
		// free(env);
		// free_all(minishell, NULL, -1);
		// exit(minishell->exit_code);
	}
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

void	last_child(t_data *minishell, char **env)
{
	// if here_doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
	{
		minishell->outfile = -1;
		free_all(minishell, NULL, -1);
		exit(1);
	}
	else
		open_outfile(minishell, outfile_count(minishell));
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
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
	{
		exec_builtin(minishell, env);
		// free(env);
		// free_all(minishell, NULL, -1);
		// exit(minishell->exit_code);
	}
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}
