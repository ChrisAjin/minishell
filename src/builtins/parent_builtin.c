/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:59:41 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/19 15:52:37 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_parent_builtin(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (0);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	// if (ft_strncmp(cmd, "unset", 6) == 0)
		// return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	which_builtin(t_data *minishell)
{
	if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
		minishell->exit_code = env_cmd(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		minishell->exit_code = cd(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
		minishell->exit_code = export(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
	// 	minishell->exit_code = unset();
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(minishell);
	return (0);
}

int	parent_builtin(t_data *minishell, char **env)
{
	if (env)
		free(env);
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
		minishell->outfile = -1;
	else
		open_outfile(minishell, outfile_count(minishell));
	if (infile_count(minishell) > 0 && minishell->infile < 0)
	{
		minishell->exit_code = 1;
		return (1);
	}
	if (outfile_count(minishell) > 0 && minishell->outfile < 0)
	{
		minishell->exit_code = 1;
		return (1);
	}
	which_builtin(minishell);
	if (minishell->infile > 0)
		close(minishell->infile);
	if (minishell->outfile > 0)
		close(minishell->outfile);
	minishell->infile = -1;
	minishell->outfile = -1;
	return (0);
}
