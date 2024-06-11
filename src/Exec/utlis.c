/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:58:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/11 15:39:36 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !!! proteger l'appel de split paths
char	**split_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	if (!env)
		return (paths);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
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

int	renew_pipe(t_data *minishell)
{
	if (minishell->temp_fd != -1)
		close(minishell->temp_fd);
	minishell->temp_fd = minishell->pip[0];
	close(minishell->pip[1]);
	if (pipe(minishell->pip) < 0)
	{
		perror("pipe error");
		return (-1);
	}
	return (0);
}

int	close_all(t_data *minishell)
{
	if (minishell->infile > 0)
		close(minishell->infile);
	if (minishell->outfile > 0)
		close(minishell->outfile);
	if (minishell->pip[0] > 0)
		close(minishell->pip[0]);
	if (minishell->pip[1] > 0)
		close(minishell->pip[1]);
	if (minishell->temp_fd > 0)
		close(minishell->temp_fd);
	return (0);
}

// que pour les childs, en cas d'erreur, apres le msg d'erreur
int	close_fds()
{
	close(0);
	close(1);
	close(2);
}

// skip juste apres le prochain pipe et skip cmd
void	skip(t_data **minishell)
{
	while ((*minishell)->token->type != PIPE)
		(*minishell)->token = (*minishell)->token->next;
	(*minishell)->token->next;
	(*minishell)->cmd = (*minishell)->cmd->next;
	(*minishell)->pipes -= 1;
}
