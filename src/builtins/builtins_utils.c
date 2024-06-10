/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:03 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 14:59:57 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd export unset et exit faut pas fork quand c'est une seule commande

// !!! tous les builtins doivent exit pour kill les childs !!! sinon exit apres exec builtin
// adapter env pour une liste chainee pas **tab

// export: regles a respecter dans les noms, voir cas s'il existe deja (ecrase l'ancien?)

// unset : echo oui | unset PATH | ls n'a pas unset PATH...

// prends en param la struct pour pouvoir tout free
int	exec_builtin(t_data *minishell)
{
	if (!minishell->cmd->cmd_param || minishell->cmd->cmd_param[0] == '\0')
		return (0);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "echo", 5) == 0)
		echo(minishell->cmd->cmd_param);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		cd(minishell->cmd->cmd_param, minishell->env);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "pwd", 4) == 0)
		pwd();
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
	// 	export(minishell->cmd->cmd_param);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
	// 	unset(minishell->cmd->cmd_param);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
		env_cmd(minishell->cmd->cmd_param, minishell->env);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(1);
	return (0);
}

char	*get_pwd()
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (!path || path[0] == '\0')
	{
		perror("getcwd");
		return (NULL);
	}
	return (path);
}
