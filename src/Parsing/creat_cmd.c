/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/14 18:02:50 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	fill_cmd(t_data *data, t_token *tmp)
{
	if (data->outfile == -1)
	{
		data->cmd->prev->skip_cmd = true;
		data->outfile = -1;
		return (true);
	}
	
	if (data->outfile == -1)
	{
		if (data->infile >= 0)
			close (data->infile);
		data->cmd->prev->skip_cmd = true;
		data->infile = -1;
		return (true);
	}
	data->cmd->prev->cmd_param = get_param(data, tmp);
	if (!data->cmd->prev->cmd_param)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (true);
}

static bool	norm(t_data *data, t_token *tmp)
{
	if (!append_cmd(&data->cmd, NULL))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!fill_cmd(data, tmp))
	{
		data->exit_code = 2;
		return (false);
	}
	return (true);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!norm(data, tmp))
		return (false);
	tmp = tmp->next;
	while (tmp != data->token)
	{
		if (tmp->prev->type == PIPE)
		{
			if (!norm(data, tmp))
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
