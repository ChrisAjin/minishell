/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:19:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/07/01 19:17:22 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	get_in(t_data *data, t_token *tmp, t_cmd *cmd)
{
	(void)cmd;
	if (tmp->type == INPUT)
	{
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
	}
	else if (tmp->type == HEREDOC)
	{
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
		if (here_doc(data, tmp->next->str) < 0)
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

static bool	get_out(t_token *tmp, t_cmd *cmd, t_data *data)
{
	(void)cmd;
	if (tmp->type == TRUNC)
	{
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
	}
	else if (tmp->type == APPEND)
	{
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
	}
	return (true);
}

bool	get_outfile(t_token *token, t_cmd *cmd, t_data *data)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_out(tmp, cmd, data))
		return (false);
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (!get_out(tmp, cmd, data))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
