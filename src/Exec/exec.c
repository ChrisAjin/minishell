/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/10 14:55:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// open dans les childs pcq chacun peut avoir ses redir
// avant la fonction exec il faut init inf et outf sur stdin et stdout ou sur -1
// gerer le cas ou on a juste un pipe a la fin ?
// comment parcourir les cmds pour les assigner au bon child ?

// struct avec
// infile // pour child
// outfile // pour child
// tab avec cmd et args (skip et fill) // pour parent
// tab de paths (if env et if PATH) // pour parent

// !!! penser a free char **env partout
int	exec(t_data *minishell)
{
	int	pipes;
	char	**env;

	pipes = pipe_count(minishell);
	env = list_to_arr(minishell->env);
	if (pipes == 0)
	{
		if (one_cmd(minishell, env) < 0)
			minishell->exit_code = 1;
		return (0);
	}
	else if (pipes >= 1)
	{
		if (exec_first_child(minishell) < 0)
		{
			minishell->exit_code = 1;
			close_all(minishell);
			return (0);
		}
		// skip qui avance les token jusqu'au prochain pipe et la struct cmd de 1 pour la prochaine
		while (minishell->cmd->next != NULL) // !!!!!!!! while pas sur la derniere cmd
		{
			if (exec_middle_childs(minishell) < 0)
			{
				minishell->exit_code = 1;
				close_all(minishell);
				return (0);
			}
			// skip vers prochaine cmd
		}
		// close temp_fd if > 0
	}
	if (exec_last_child(minishell) < 0)
	{
		minishell->exit_code = 1;
		close_all(minishell);
		return (0);
	}
	close_all(minishell);
	return (0);
}

int	exec_last_child(t_data *minishell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	last_child(minishell);
	wait_and_error(minishell, pid);
	return (0);
}

int	exec_first_child(t_data *minishell)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (-1);
	}
	first_child(minishell);
	return (0);
}

int	one_cmd(t_data *minishell, char **env)
{
	int	pid;

	parent_builtin(minishell);
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

int	pipe_count(t_data *minishell)
{
	int	pipes;
	t_token	*tmp;

	pipes = 0;
	tmp = minishell->token;
	tmp = tmp->next; // le premier ne peut pas etre un pipe (unexpected token)
	while (tmp != minishell->token)
	{
		if (tmp->type == PIPE)
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}
