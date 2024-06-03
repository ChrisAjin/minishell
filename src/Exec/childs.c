/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/03 18:16:53 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

int	only_child(t_data *minishell)
{
	int	infile;
	int	outfile;
	// if (minishell->token->type == 2)
		// exec_here_doc
	// if redir
		// open (outf soit > et >>)
	if (infile != 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (outfile != 1)
		if (dup2(outfile, STDOUT_FILENO) < 0)
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
	int	infile;
	int	outfile;
	// if here_doc
	// mettre inf et outf a -1 et open (inf et outf) si redir
	if (infile > 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	if (outfile > 0)
		if (dup2(outfile, STDOUT_FILENO) < 0)
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
	int	infile;
	int	outfile;
	// chercher la bonne cmd avec cmd_nbr
	// if here doc
	// if redir open
	if (infile > 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	if (outfile > 0)
		if (dup2(outfile, STDOUT_FILENO) < 0)
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
	int	infile;
	int	outfile;
	// if here_doc
	// if redir --> open (inf et outf)
	if (infile > 0)
		if (dup2(infile, STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	else
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, cmd_nbr);
	if (outfile != 1)
		if (dup2(outfile, STDOUT_FILENO) < 0)
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
