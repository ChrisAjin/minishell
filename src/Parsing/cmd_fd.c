/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:40:30 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/14 11:15:22 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static int	open_file(t_data *data, char *filename, int type)
{
	int	fd;
    (void)data;
	fd = -2;
	//if (type == HEREDOC)
		//fd = here_doc(data, filename);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

static bool	get_in(t_data *data, t_token *tmp, t_cmd *cmd)
{
    (void)cmd;
	if (tmp->type == HEREDOC)
	{
		if (data->infile >= 0)
			close(data->infile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
		data->infile = open_file(data, tmp->next->str, HEREDOC);
		if (data->infile == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_in(data, tmp, cmd))
		return (false);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp->type != PIPE && tmp != data->token)
	{
		if (!get_in(data, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
