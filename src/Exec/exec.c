/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/03 18:11:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// open dans les childs pcq chacun peut avoir ses redir
// avant la fonction exec il faut init inf et outf sur stdin et stdout ou sur -1
// gerer le cas ou on a juste un pipe a la fin ?
// comment parcourir les cmds pour les assigner au bon child ?

// int	skip_prev(t_data *minishell, int cmd_nbr)
// {
	
// }

int	type_count(t_data *minishell, int type, int cmd_nbr)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	// avancer jusqu'au debut du pipe de la cmd qui correspond
	while (minishell->token)
	{
		if (minishell->token->type == CMD)
			cmd += 1;
		if (cmd == cmd_nbr)
			break ;
		minishell->token = minishell->token->next;
	}
	while (minishell->token)
	{
		if (minishell->token->type == PIPE)
			break ;
		minishell->token = minishell->token->next;
	}
	while (minishell->token && minishell->token->type != PIPE)
	{
		if (minishell->token->type == type)
			i++;
		minishell->token = minishell->token->next;
	}
	return (i);
}

int	exec(t_data *minishell)
{
	int	cmd_nbr;

	cmd_nbr = 0;
	if (minishell->ac == 0)
		return (0); // init exit code
	else if (minishell->ac == 1)
	{
		if (one_cmd(minishell) < 0)
		{
			// exit code = 1;
			// return (1);
		}
	}
	else if (ac > 1)
	{
		// first child
		// cmd_nbr += 1
		// while (cmd_nbr < ac)
			// exec middle childs
			// cmd_nbr++;
		// close temp_fd
	}
	// exec last child
	// close all
	// free tout
	// exit_code = wait and error(pid only child ou last child);
	// return 0
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
		// only child
	// init exit code
	return (0);
}

// pour commande sans path
// int	find_and_exec(t_data *minishell, int cmd_nbr)
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
// int	exec_path(t_data *minishell, int cmd_nbr)
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
