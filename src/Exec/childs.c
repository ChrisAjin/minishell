/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/06 18:36:24 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// j'ai retire empty cmd pcq gere dans le parsing normalement
// peut etre remplace par un check de skip and fill si elle est a NULL

int	only_child(t_data *minishell)
{
	// if (minishell->token->type == 2)
		// exec_here_doc
	open_infile(minishell, 1, infile_count(minishell, 1));
	if (infile_count(minishell, 1) != 0 && minishell->cmd->infile < 0)
		minishell->cmd->outfile = -1;
	else
		open_outfile(minishell, 1, outfile_count(minishell, 1));
	if (minishell->cmd->infile > 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, minishell->cmd->infile, minishell->cmd->outfile);
	if (minishell->cmd->outfile > 0)
		if (dup2(minishell->cmd->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, minishell->cmd->infile, minishell->cmd->outfile);
	close_all(minishell, minishell->cmd->infile, minishell->cmd->outfile);
	// if (ft_strchr(command[0], '/') != 0)
	// 	return (exec_path);
	// exec builtin
	// 	exit 0
	// return (exec);
}

int	first_child(t_data *minishell, int child_nbr)
{
	int	infile;
	int	outfile;
	// skip prev
	// if here_doc
	// mettre inf et outf a -1 et open (inf et outf) si redir
	if (infile > 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	if (outfile > 0)
		if (dup2(outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	close_all(minishell, infile, outfile);
	// if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}

// middle child avec temp fd et child_nbr
int	middle_child(t_data *minishell, int child_nbr)
{
	int	infile;
	int	outfile;
	// chercher la bonne cmd avec child_nbr
	// if here doc
	// if redir open
	if (infile > 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	if (outfile > 0)
		if (dup2(outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	close_all(minishell, infile, outfile);
	// if builtin
		// return exec builtin
	// if (ft_strchr(cmd, '/') != 0)
		// return exec path
	// return find and exec
}

int	last_child(t_data *minishell, int child_nbr)
{
	int	infile;
	int	outfile;
	// if here_doc
	// if redir --> open (inf et outf)
	if (infile > 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	if (outfile != 1)
		if (dup2(outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	else
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, infile, outfile);
	close_all(minishell, infile, outfile);
	empty_cmd(minishell->token->str);
	//  if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// if builtin
		// return exec builtin
	// return (exec);
}
