/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/28 15:57:42 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

// fonction pour voir s'il y a ca dans le bloc <<
// fonction pour voir s'il y a une redir inf
// fonction pour voir s'il y a une redir outf

int	only_child(t_data *minishell)
{
	// if <<
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
	// if (!command || command[0] == '\0')
	// {
	// 	ft_putendl_fd("Command not found.", 2);
	// 	close_fds();
	// 	exit(127);
	// }
	// if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// is_builtin(minishell);
	// return (exec);
}

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
	// if (!command || command[0] == '\0')
	// {
	// 	ft_putendl_fd("Command not found.", 2);
	// 	exit(127);
	// }
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
	// if (!command || command[0] == '\0')
	// {
	// 	ft_putendl_fd("Command not found.", 2);
	// 	exit(127);
	// }
	//  if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// return (exec);
}
