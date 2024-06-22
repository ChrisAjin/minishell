/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:13:14 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/19 15:06:07 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// s'assurer qu'avec here doc l'infile sert a r
// tester voir s'il n'y a pas de pb de pipe ou s'il faut renew_pipe
// void	is_here_doc(t_data *minishell, char **env, int read, int write) // write = -1 pour last child
// {
// 	if (minishell->cmd->skip_cmd == true)
// 	{
// 		// free(env);
// 		// free_all(minishell, NULL, -1);
// 		exit(0);
// 	}
// 	open_inf_outf(minishell);
// 	while (minishell->token->type != HEREDOC)
// 		minishell->token = minishell->token->next;
// 	minishell->token = minishell->token->next;
// 	ft_putstr_fd(minishell->token->str, minishell->pip[1]); // putstr i++ ou s
// 	if (dup2(read, STDIN_FILENO) < 0) // pip[0] ou temp fd si c'est un middle jcrois
// 		dup2_error(minishell, env);
// 	if (minishell->outfile > 0)
// 	{
// 		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
// 			dup2_error(minishell, env);
// 	}
// 	else if (write > 0)
// 	{
// 		if (dup2(write, STDOUT_FILENO) < 0) // ou dans stdout si c'est last
// 			dup2_error(minishell, env);
// 	}
// 	close_all(minishell);
// 	if (ft_strchr(minishell->cmd->cmd_param[0], '/') == 0)
// 		exec_path(minishell, env);
// 	find_and_exec(minishell, env);
// }

void	only_child(t_data *minishell, char **env)
{
	// if here_doc
	open_inf_outf(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all(minishell);
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
		exec_builtin(minishell, env);
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

void	first_child(t_data *minishell, char **env)
{
	// if here_doc
	open_inf_outf(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all(minishell);
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
		exec_builtin(minishell, env);
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

// middle child avec temp fd et child_nbr
void	middle_child(t_data *minishell, char **env)
{
	// if here doc
	open_inf_outf(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->temp_fd, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->pip[1], STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all(minishell);
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
		exec_builtin(minishell, env);
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}

void	last_child(t_data *minishell, char **env)
{
	// if here_doc
	open_inf_outf(minishell);
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	else
	{
		if (dup2(minishell->pip[0], STDIN_FILENO) < 0)
			dup2_error(minishell, env);
	}
	if (minishell->outfile > 0)
	{
		if (dup2(minishell->outfile, STDOUT_FILENO) < 0)
			dup2_error(minishell, env);
	}
	close_all(minishell);
	if (minishell->cmd->skip_cmd == true)
	{
		free(env);
		free_all(minishell, NULL, -1);
		exit(0);
	}
	if (is_builtin(minishell->cmd->cmd_param[0]) == 1)
		exec_builtin(minishell, env);
	if (ft_strchr(minishell->cmd->cmd_param[0], '/') != 0) // ou if access == 0
		exec_path(minishell, env);
	find_and_exec(minishell, env);
}
