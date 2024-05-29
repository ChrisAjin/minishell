/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/29 14:14:27 by inbennou         ###   ########.fr       */
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
	// is_builtin(minishell);
	// return (exec);
}

// init skip_cmd a true apres l'avoir exec?
int	first_child(t_data *minishell)
{
	// if here_doc
	if (minishell->cmd->infile != 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
		dup2_error(minishell);
	// close_all(minishell);
	// unlink("here_doc");
	empty_cmd(minishell->token->str);
	// if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// return (exec);
}

int	last_child(t_data *minishell)
{
	// if here_doc
	if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
		dup2_error(minishell);
	if (minishell->cmd->outfile != 1)
		if (dup2(minishell->cmd->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell);
	close_all(minishell);
	empty_cmd(minishell->token->str);
	//  if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// return (exec);
}
