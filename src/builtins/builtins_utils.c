/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:31:03 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 14:44:50 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin(t_data *minishell, char **env)
{
	if (ft_strncmp(minishell->cmd->cmd_param[0], "echo", 5) == 0)
		free_and_exit(minishell, env, echo(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "pwd", 4) == 0)
		free_and_exit(minishell, env, pwd(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
		free_and_exit(minishell, env, env_cmd(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		free_and_exit(minishell, env, cd(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
		free_and_exit(minishell, env, export(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
		free_and_exit(minishell, env, unset(minishell));
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(minishell);
}

int	is_builtin(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

char	*get_pwd(void)
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

void	free_and_exit(t_data *minishell, char **env, int ret)
{
	free(env);
	free_all(minishell, NULL, -1);
	exit(ret);
}

int	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) == true)
			return (1);
		i++;
	}
	return (0);
}
