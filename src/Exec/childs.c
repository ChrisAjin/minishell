/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 17:43:35 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// faire un empty cmd check

// dans le meme child, si l'infile n'existe pas, alors l'outfile n'est pas cree

int	only_child(t_data *minishell)
{
	// if (minishell->token->type == 2)
		// exec_here_doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
		minishell->outfile = -1;
	else
		open_outfile(minishell, outfile_count(minishell));
	if (minishell->infile > 0)
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (minishell->outfile > 0)
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell);
	close_all(minishell);
	if (!minishell->cmd->cmd_param || minishell->cmd->cmd_param[0] == '\0')
		exit(1);
	if (exec_builtin(minishell) < 0)
		exit(0);
	// if (ft_strchr(command[0], '/') != 0) // ou if access == 0
	// 	return (exec_path);
	// exec builtin
	// 	exit 0
	// return (exec);
}

int	first_child(t_data *minishell)
{
	// if here_doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
		minishell->outfile = -1;
	else
		open_outfile(minishell, outfile_count(minishell));
	if (minishell->infile > 0)
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (minishell->outfile > 0)
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell);
	close_all(minishell);
	// if (ft_strchr(command, '/') != 0) // ou if access == 0
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}

// middle child avec temp fd et child_nbr
int	middle_child(t_data *minishell)
{
	// if here doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
		minishell->outfile = -1;
	else
		open_outfile(minishell, outfile_count(minishell));
	if (minishell->infile > 0)
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (minishell->outfile > 0)
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell);
	close_all(minishell);
	// if builtin
		// return exec builtin
	// if (ft_strchr(cmd, '/') != 0) // ou if access == 0
		// return exec path
	// return find and exec
}

int	last_child(t_data *minishell)
{
	// if here_doc
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
		minishell->outfile = -1;
	else
		open_outfile(minishell, outfile_count(minishell));
	if (minishell->infile > 0)
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (minishell->outfile > 0)
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell);
	close_all(minishell);
	//  if (ft_strchr(command, '/') != 0) // ou if access == 0
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}
