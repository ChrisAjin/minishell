/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/06 12:52:58 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_exec
// {
// 	int				infile;
// 	int				outfile;
// 	int				temp_fd;
// 	char			**paths;
// }				t_exec;

// void	init_exec(t_exec *exec, t_data *minishell)
// {
// 	exec->infile = -1;
// 	exec->outfile = -1;
// 	exec->temp_fd = -1;
// 	exec->paths = split_path(minishell->env);
// 	// exec->cmd_param = fill_cmd();
// }

// open dans les childs pcq chacun peut avoir ses redir
// avant la fonction exec il faut init inf et outf sur stdin et stdout ou sur -1
// gerer le cas ou on a juste un pipe a la fin ?
// comment parcourir les cmds pour les assigner au bon child ?

// <
// infile
// ls
// |
// echo
// a
// |
// unset
// PATH

// skip (child nbr - 1) pipe
char	**skip_and_fill(t_data *minishell, int child_nbr)
{
	char	**cmd;

	cmd = NULL;
	while (minishell->token && minishell->token->type != PIPE)
		minishell->token = minishell->token->next;
	if (minishell->token)
		minishell->token = minishell->token->next;
	while (minishell->token && minishell->token->type != PIPE)
	{
		cmd[0] = ft_strdup(minishell->token->str);
	}
}

// struct avec
// infile // pour child
// outfile // pour child
// tab avec cmd et args (skip et fill) // pour parent
// tab de paths (if env et if PATH) // pour parent

int	exec(t_data *minishell)
{
	int	child_nbr;

	child_nbr = 0;
	// fonction qui recup env dans un char **
	if (type_count(minishell, PIPE, 0) == 0)
	{
		if (one_cmd(minishell) < 0)
			minishell->exit_code = 1;
		return (0);
	}
	else if (type_count(minishell, PIPE, 0) >= 1)
	{
		if (exec_first_child(minishell, child_nbr) < 0)
		{
			minishell->exit_code = 1;
			close_all(minishell, -1, -1);
			return (0);
		}
		child_nbr += 1;
		// -2 pcq pas la derniere cmd et il y a un pipe de moins qu'il y a de child
		while (child_nbr < type_count(minishell, PIPE, 0) - 2)
		{
			if (exec_middle_childs(minishell, child_nbr) < 0)
			{
				minishell->exit_code = 1;
				close_all(minishell, -1, -1);
				return (0);
			}
			child_nbr += 1;
		}
		// close temp_fd if > 0
	}
	if (exec_last_child(minishell, child_nbr) < 0)
	{
		minishell->exit_code = 1;
		close_all(minishell, -1, -1);
		return (0);
	}
	close_all(minishell, -1, -1);
	return (0);
}

int	exec_last_child(t_data *minishell, int child_nbr)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	last_child(minishell, child_nbr);
	wait_and_error(minishell, pid);
	return (0);
}

int	exec_first_child(t_data *minishell, int child_nbr)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	first_child(minishell, child_nbr);
	return (0);
}

int	one_cmd(t_data *minishell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	if (pid == 0)
		only_child(minishell);
	wait_and_error(minishell, pid);
	return (0);
}

// pour commande sans path
// int	find_and_exec(t_data *minishell, int child_nbr)
// {
	// split paths
	// split args
	// proteger splits
	// while (paths)
	// {
		// join paths[i] avec /
		// path/cmd = join ca avec la cmd
		// proteger join
		// if (access(path/cmd, F_OK | X_OK) >= 0)
			// if (execve(path/cmd, args, envp) < 0)
				// return exec fail
		// free le join
	// }
	// return command not found
// }

// pour commande avec path
// int	exec_path(t_data *minishell, int child_nbr)
// {
	// split args
	// proteger split
	// if (access(args[0], F_OK | X_OK) == 0)
		// if (execve(args[0], args, envp) < 0)
			// exec fail
	// if (access(args[0], F_OK) < 0)
		// no such file
	// permision denied
// }

// int	type_count(t_data *minishell, int type, int child_nbr)
// {
// 	int	i;
// 	int	cmd;

// 	i = 0;
// 	cmd = 0;
// 	// avancer jusqu'au debut du pipe de la cmd qui correspond
// 	while (minishell->token)
// 	{
// 		if (minishell->token->type == CMD)
// 			cmd += 1;
// 		if (cmd == child_nbr)
// 			break ;
// 		minishell->token = minishell->token->next;
// 	}
// 	while (minishell->token)
// 	{
// 		if (minishell->token->type == PIPE)
// 			break ;
// 		minishell->token = minishell->token->next;
// 	}
// 	while (minishell->token && minishell->token->type != PIPE)
// 	{
// 		if (minishell->token->type == type)
// 			i++;
// 		minishell->token = minishell->token->next;
// 	}
// 	return (i);
// }
