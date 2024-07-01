/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:44:38 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 17:01:25 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_data *minishell)
{
	t_token	*temp;
	int		infiles;
	int		outfiles;

	temp = minishell->token->next;
	infiles = 0;
	outfiles = 0;
	minishell->inf_c = infile_count(minishell);
	minishell->outf_c = outfile_count(minishell);
	while (temp->type != 0 && temp->type != PIPE)
	{
		if (temp->prev->type == INPUT)
		{
			minishell->infile = open_in(minishell, temp, &infiles);
			if (minishell->infile < 0)
				exit(1);
		}
		else if ((temp->prev->type == TRUNC || temp->prev->type == APPEND))
			minishell->outfile = open_out(minishell, temp, &outfiles);
		temp = temp->next;
	}
}

int	open_out(t_data *minishell, t_token *temp, int *outfiles)
{
	int	fd_out;

	fd_out = 0;
	if (temp->type == TRUNC)
		fd_out = open(temp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(temp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out < 0)
		perror(temp->str);
	*outfiles += 1;
	if (minishell->outf_c != *outfiles)
		close(fd_out);
	return (fd_out);
}

int	open_in(t_data *minishell, t_token *temp, int *infiles)
{
	int	fd_in;

	fd_in = 0;
	fd_in = open(temp->str, O_RDONLY, 0644);
	if (fd_in < 0)
		perror(temp->str);
	*infiles += 1;
	if (minishell->inf_c != *infiles)
		close(fd_in);
	return (fd_in);
}

int	infile_count(t_data *minishell)
{
	t_token	*tmp;
	int		redir;

	tmp = minishell->token;
	redir = 0;
	if (tmp->type == INPUT)
		redir++;
	tmp = tmp->next;
	while (tmp->type != 0 && tmp->type != PIPE)
	{
		if (tmp->type == INPUT)
			redir++;
		tmp = tmp->next;
	}
	return (redir);
}

int	outfile_count(t_data *minishell)
{
	t_token	*tmp;
	int		redir;

	tmp = minishell->token;
	redir = 0;
	if (tmp->type == TRUNC || tmp->type == APPEND)
		redir++;
	tmp = tmp->next;
	while (tmp->type != 0 && tmp->type != PIPE)
	{
		if (tmp->type == TRUNC || tmp->type == APPEND)
			redir++;
		tmp = tmp->next;
	}
	return (redir);
}
