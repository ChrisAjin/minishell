/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:03 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 16:31:18 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// cd export unset et exit faut pas fork quand c'est une seule commande

// export: regles a respecter dans les noms, voir cas s'il existe deja (ecrase l'ancien?)

// prends en param la struct pour pouvoir tout free
void	exec_builtin(t_data *minishell, char **env)
{
	if (ft_strncmp(minishell->cmd->cmd_param[0], "echo", 5) == 0)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(echo(minishell));
	}
	if (ft_strncmp(minishell->cmd->cmd_param[0], "pwd", 4) == 0)
		exit(pwd(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
		exit(env_cmd(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		exit(cd(minishell));
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
		// exit(export());
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
		// exit(unset());
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(minishell);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	// if (ft_strncmp(cmd, "export", 7) == 0)
		// return (1);
	// if (ft_strncmp(cmd, "unset", 6) == 0)
		// return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
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
