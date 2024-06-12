/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:59:41 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/12 12:58:57 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utiliser des cmd differentes dans la parent pour ne pas double free?
// init minishell->exit_code
// faire des fnctions qui exit pas sinon exit ailleurs pour les childs
// int	parent_builtin(t_data *minishell)
// {
// 	if (!minishell->cmd->cmd_param || minishell->cmd->cmd_param[0] == NULL)
// 		return (1);
// 	// if redir open et dup2?
// 	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
// 		cd(minishell);
// 	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
// 	// 	export(minishell->cmd->cmd_param);
// 	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
// 	// 	unset(minishell->cmd->cmd_param);
// 	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
// 		exit_shell(minishell);
// 	return (0);
// }

// si qqch se passe mal on init exit code
int	parent_builtin(t_data *minishell, char **env)
{
	if (env)
		free(env);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "echo", 5) == 0)
	// 	echo(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "pwd", 4) == 0)
	// 	pwd(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
	// 	env_cmd(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
	// 	cd(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
		// export();
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
		// unset();
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(minishell);
	return (0);
}
