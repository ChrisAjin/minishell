/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:17:21 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/27 15:16:29 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init_fds(t_data *minishell)
{
	minishell->temp_fd = -1;
	minishell->pip[0] = -1;
	minishell->pip[1] = -1;
}

void	close_fds(void)
{
	close(0);
	close(1);
}

void	clean_exit(t_data *minishell, char **env, int ret)
{
	close_all(minishell);
	close_fds();
	free_and_exit(minishell, env, ret);
}

void	middle_dup2(t_data *minishell, char **env)
{
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
}
