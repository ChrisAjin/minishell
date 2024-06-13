/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:59:41 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 16:53:02 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	which_builtin(t_data *minishell)
{
	if (ft_strncmp(minishell->cmd->cmd_param[0], "echo", 5) == 0)
		minishell->exit_code = echo(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "pwd", 4) == 0)
		minishell->exit_code = pwd(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "env", 4) == 0)
		minishell->exit_code = env_cmd(minishell);
	if (ft_strncmp(minishell->cmd->cmd_param[0], "cd", 3) == 0)
		minishell->exit_code = cd(minishell);
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "export", 7) == 0)
	// 	minishell->exit_code = export();
	// if (ft_strncmp(minishell->cmd->cmd_param[0], "unset", 6) == 0)
	// 	minishell->exit_code = unset();
	if (ft_strncmp(minishell->cmd->cmd_param[0], "exit", 5) == 0)
		exit_shell(minishell);
	return (0);
}

// dup2 dans le parent et re dup2 pour remettre sur stdin et stdout
// init inf et outf a -1 aussi a la fin
int	parent_builtin(t_data *minishell)
{
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
		minishell->outfile = -1;
	else
		open_outfile(minishell, outfile_count(minishell));
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
		{
			perror("dup2 error"); // retirer
			return (-1);
		}
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
		{
			perror("dup2 error"); // retirer
			return (-1);
		}
	}
	which_builtin(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(STDIN_FILENO, minishell->infile) < 0)
		{
			perror("dup2 error"); // retirer
			return (-1);
		}
	}
	if (minishell->outfile > 0)
	{
		if (dup2(STDOUT_FILENO, minishell->outfile) < 0)
		{
			perror("dup2 error");
			return (-1);
		}
	}
	if (minishell->infile > 0)
		close(minishell->infile);
	if (minishell->outfile > 0)
		close(minishell->outfile);
	return (0);
}
