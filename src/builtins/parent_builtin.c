/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:59:41 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 15:01:06 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// init minishell->exit_code
// faire des fnctions qui exit pas sinon exit ailleurs pour les childs
int	parent_builtin(t_data *minishell)
{
	if (!minishell->cmd->cmd_param || minishell->cmd->cmd_param[0] == '\0')
		return (0);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		cd_parent(minishell->cmd->cmd_param, minishell->env);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
	// 	export_parent(minishell->cmd->cmd_param);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
	// 	unset_parent(minishell->cmd->cmd_param);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell_parent(1);
	return (0);
}

