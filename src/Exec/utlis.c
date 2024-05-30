/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:58:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/30 14:54:43 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

// !!! proteger l'appel de split paths
char	**split_paths(t_list *env)
{
	t_list	*tmp;
	int		i;
	char	**paths;

	tmp = env;
	i = 0;
	paths = NULL;
	if (!env)
		return (paths);
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PATH", 4) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp->str + 5, ':');
	return (paths);
}

// waitpid renvoie -1 quand il n'y a plus d'enfant a attendre
void	wait_and_error(t_data *minishell, int pid_lastchild)
{
	int	status;
	int	error;
	int	current_pid;

	error = 0;
	while (1)
	{
		current_pid = waitpid(-1, &status, 0);
		if (pid_lastchild == current_pid)
		{
			if (WIFEXITED(status))
				error = WEXITSTATUS(status);
		}
		if (current_pid < 0)
			break ;
	}
	minishell->exit_code = error;
}

void	exec_middle_childs(t_data *minishell, int ac)
{
	int	pid;

	// while cmd != ac, next ?
	renew_pipe(minishell);
	pid = fork();
	// proteger fork
	// if (pid == 0)
		// middle child
	// equivalent de i++
	// if derniere cmd
		// close temp fd
}

// ajouter temp fd a la struc avec pip
// void	renew_pipe(t_data *minishell)
// {
// 	if (minishell->temp_fd != -1)
// 		close(minishell->temp_fd);
// 	minishell->temp_fd = minishell->pip[0];
// 	close(minishell->pip[1]);
// 	if (pipe(minishell->pip) < 0)
// 		close_and_error(minishell, "Pipe error");
// }

// avoir cmd_nbr pour savoir quels fds close ?
int	close_all(t_data *minishell, int cmd_nbr)
{
	if (minishell->cmd->infile > 0)
		close(minishell->cmd->infile);
	if (minishell->cmd->outfile > 0)
		close(minishell->cmd->outfile);
	close(minishell->pip[0]);
	close(minishell->pip[1]);
	// if (minishell->temp_fd > 0)
	// 	close(minishell->temp_fd);
	return (0);
}

// que pour les childs, en cas d'erreur, apres le msg d'erreur
int	close_fds()
{
	close(0);
	close(1);
	close(2);
}
