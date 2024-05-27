/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/27 17:29:35 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

int	only_child(t_data *minishell)
{
	// if here_doc
		// exec_here_doc
	// if redir
		// open
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
	// 	exit(127);
	// }
	// if (ft_strchr(command, '/') != 0)
	// 	return (exec_path);
	// is_builtin(minishell);
	// return (exec);
}

void	exec_here_doc(t_data *minishell)
{
	// ouvrir un fichier temp ou ecrire dans le pipe
	// revoir gnl
	// voir s'il y a une cmd avec le here doc ou pas
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
