/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:44:38 by inbennou          #+#    #+#             */
/*   Updated: 2024/06/13 18:50:49 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_count(t_data *minishell)
{
	t_token	*tmp;
	int	redir;

	tmp = minishell->token;
	redir = 0;
	if (tmp->type == INPUT)
		redir++;
	tmp = tmp->next;
	while (tmp != minishell->token && tmp->type != PIPE)
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
	int	redir;

	tmp = minishell->token;
	redir = 0;
	if (tmp->type == TRUNC || tmp->type == APPEND)
		redir++;
	tmp = tmp->next;
	while (tmp != minishell->token && tmp->type != PIPE)
	{
		if (tmp->type == TRUNC || tmp->type == APPEND)
			redir++;
		tmp = tmp->next;
	}
	return (redir);
}

void	open_infile(t_data *minishell, int inf_count)
{
	t_token *tmp;
	int	fd;
	int	inf_nbr;

	tmp = minishell->token->next;
	fd = -1;
	inf_nbr = 0;
	while (tmp != minishell->token && tmp->type != PIPE)
	{
		if (tmp->prev->type == INPUT)
		{
			fd = open(tmp->str, O_RDONLY, 0644);
			if (fd < 0)
				perror(tmp->str); // ajouter minishell->exit_code = 1;
			inf_nbr++;
			if (inf_nbr != inf_count)
				close(fd);
		}
		if (tmp)
			tmp = tmp->next;
	}
	minishell->infile = fd;
}

// !!! si on n'arrive pas a open l'infile on open pas l'outfile !!!
void	open_outfile(t_data *minishell, int outf_count)
{
	t_token *tmp;
	int	fd;
	int	inf_nbr;

	tmp = minishell->token->next;
	fd = -1;
	inf_nbr = 0;
	while (tmp != minishell->token && tmp->type != PIPE)
	{
		if (tmp->prev->type == TRUNC || tmp->prev->type == APPEND)
		{
			if (tmp->type == TRUNC)
				fd = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(tmp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				perror(tmp->str); // ajouter minishell->exit_code = 1;
			inf_nbr++;
			if (inf_nbr != outf_count)
				close(fd);
		}
		if (tmp)
			tmp = tmp->next;
	}
	minishell->outfile = fd;
}
