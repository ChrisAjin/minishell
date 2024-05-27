/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/27 14:26:26 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

// first child:
// s'il y a une redir on fait le premier dup2
// s'il y a plusieurs commandes on fait le deuxieme
// close les pipes
// 

int	first_child(t_data *minishell)
{
	if (minishell->cmd->infile != 0)
		if (dup2(minishell->cmd->infile, STDIN_FILENO) < 0)
			dup2_error(minishell);
	if (minishell->cmd->outfile != 1)
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
