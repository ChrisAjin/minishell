/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:03 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 19:07:38 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd export unset et exit faut pas fork quand c'est une seule commande

// !!! tous les builtins doivent exit pour kill les childs !!! sinon exit apres exec builtin

// export: regles a respecter dans les noms, voir cas s'il existe deja (ecrase l'ancien?)

// prends en param la struct pour pouvoir tout free
int	exec_builtin(t_data *minishell)
{
	if (ft_strncmp(minishell->cmd->cmd_param[0], "echo", 5) == 0)
		echo(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "pwd", 4) == 0)
		pwd(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
		env_cmd(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		exit(cd(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
		// exit(export());
	if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
		// exit(unset());
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(minishell);
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
