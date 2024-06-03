/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:40 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/03 16:13:25 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool fill_cmd(t_data *data, t_token *tmp)
{
    if (!get_infile(data, tmp, data->cmd->prev) && \
        data->cmd->prev->infile != -1)
        return (false);
    if (data->cmd->prev->infile == -1)
    {
        data->cmd->prev->skip_cmd = true;
        data->cmd->prev->outfile = -1;
        return (true);
    }
    if (!get_outfile(tmp, data->cmd->prev, data) && data->cmd->prev->outfile \
        != -1)
        return (false);
    if(data->cmd->prev->outfile == -1)
    {
        if (data->cmd->prev->infile >= 0)
            close (data->cmd->prev->infile);
        data->cmd->prev->skip_cmd = true;
        data->cmd->prev->infile = -1;
        return (true);
    }
    data->cmd->prev->cmd_param = get_param(data, tmp);
    if (!data->cmd->prev->cmd_param)
        free_all(data, ERR_MALLOC, EXT_MALLOC);
    return (true);
}
static bool norm(t_data *data, t_token *tmp)
{
    if (!add_list_cmd(&data->cmd, -2, -2, NULL))
        free_all(data, ERR_MALLOC, EXT_MALLOC);
    (void)tmp;
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