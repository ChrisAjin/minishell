/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/11 17:42:48 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool fill_cmd(t_data *data, t_token *tmp)
{
    data->cmd->prev->cmd_param = get_param(data, tmp);
    if (!data->cmd->prev->cmd_param)
        free_all(data, ERR_MALLOC, EXT_MALLOC);
    return (true);
}

static bool norm(t_data *data, t_token *tmp)
{
    if (!add_list_cmd(&data->cmd, NULL))
        free_all(data, ERR_MALLOC, EXT_MALLOC);
    if (!fill_cmd(data, tmp))
	{
		data->exit_code = 2;
		return (false);
	}
    return (true);
}
bool create_list_cmd(t_data *data)
{
    t_token *tmp;

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