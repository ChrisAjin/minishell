/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/30 15:10:09 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

int	only_child(t_data *minishell)
{
	// if (minishell->token->type == 2)
		// exec_here_doc
	// if redir
		// open (outf soit > et >>)
	if (minishell->cmd->infile != 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (minishell->cmd->outfile != 1)
		if (dup2(minishell->cmd->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell);
	// close_all(minishell);
	empty_cmd(minishell->token->str);
	// if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}

// init skip_cmd a true apres l'avoir exec? (dans le parent)
int	first_child(t_data *minishell, int cmd_nbr)
{
	// if here_doc
	// if redir --> open (inf et outf)
	if (minishell->cmd->infile > 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	if (minishell->cmd->outfile > 0)
		if (dup2(minishell->cmd->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	// close_all(minishell);
	empty_cmd(minishell->token->str);
	// if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}

// middle child avec temp fd et cmd_nbr
int	middle_child(t_data *minishell, int cmd_nbr)
{
	// chercher la bonne cmd avec cmd_nbr
	// if here doc
	// if redir open
	if (minishell->cmd->infile > 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	if (minishell->cmd->outfile > 0)
		if (dup2(minishell->cmd->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	// close_all(minishell)
	// if builtin
		// return exec builtin
	// if (ft_strchr(cmd, '/') != 0)
		// return exec path
	// return find and exec
}

int	last_child(t_data *minishell, int cmd_nbr)
{
	// if here_doc
	// if redir --> open (inf et outf)
	if (minishell->cmd->infile > 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	if (minishell->cmd->outfile != 1)
		if (dup2(minishell->cmd->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	// close_all(minishell);
	empty_cmd(minishell->token->str);
	//  if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}
