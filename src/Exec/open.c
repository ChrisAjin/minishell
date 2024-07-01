/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:44:38 by inbennou          #+#    #+#             */
/*   Updated: 2024/07/01 13:56:19 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	open_files(t_data *minishell)
// {
// 	t_token	*temp;

// 	temp = minishell->token;
// 	while (temp->next != minishell->token)
// 	{
// 		if (temp->type == INPUT || temp->type == APPEND || temp->type == TRUNC)
// 		{
			
// 		}
// 	}
// }

// ouvrir les fichiers dans l'ordre, si un infile s'ouvre pas stop
int	open_inf_outf(t_data *minishell)
{
	open_infile(minishell, infile_count(minishell));
	if (infile_count(minishell) != 0 && minishell->infile < 0)
	{
		minishell->outfile = -1;
		free_all(minishell, NULL, -1);
		exit(1);
	}
	else
		open_outfile(minishell, outfile_count(minishell));
	if (infile_count(minishell) > 0 && minishell->infile < 0)
		exit(1);
	if (outfile_count(minishell) > 0 && minishell->outfile < 0)
		exit(1);
	return (0);
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

void	open_infile(t_data *minishell, int inf_count)
{
	t_token	*tmp;
	int		fd;
	int		inf_nbr;

	tmp = minishell->token->next;
	fd = -1;
	inf_nbr = 0;
	while (tmp->type != 0 && tmp->type != PIPE)
	{
		if (tmp->prev->type == INPUT)
		{
			fd = open(tmp->str, O_RDONLY, 0644);
			if (fd < 0)
				perror(tmp->str);
			inf_nbr++;
			if (inf_nbr != inf_count)
				close(fd);
		}
		if (tmp)
			tmp = tmp->next;
	}
	minishell->infile = fd;
}

void	open_outfile(t_data *minishell, int outf_count)
{
	t_token	*tmp;
	int		fd;
	int		inf_nbr;

	tmp = minishell->token->next;
	fd = -1;
	inf_nbr = 0;
	while (tmp->type != 0 && tmp->type != PIPE)
	{
		if (tmp->prev->type == TRUNC || tmp->prev->type == APPEND)
		{
			if (tmp->prev->type == TRUNC)
				fd = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(tmp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				perror(tmp->str);
			inf_nbr++;
			if (inf_nbr != outf_count)
				close(fd);
		}
		tmp = tmp->next;
	}
	minishell->outfile = fd;
}
