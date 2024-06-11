/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:59:41 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/11 17:13:24 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utiliser des cmd differentes dans la parent pour ne pas double free?
// init minishell->exit_code
// faire des fnctions qui exit pas sinon exit ailleurs pour les childs
int	parent_builtin(t_data *minishell)
{
	if (!minishell->cmd->cmd_param || minishell->cmd->cmd_param[0] == '\0')
		return (1);
	// if redir open et dup2?
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		cd(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
	// 	export(minishell->cmd->cmd_param);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
	// 	unset(minishell->cmd->cmd_param);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(1);
	return (0);
}

