/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:03:43 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/28 16:19:42 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int count_args(t_data *data, t_token *token)
{
    int count;
    t_token *tmp;

    count = 0;
    tmp = token;
    if (tmp->type == CMD || (tmp->type == ARG && \
        tmp->prev != data->token->prev && tmp->prev->type > 5))
        count ++;
    tmp = tmp->next;
    while (tmp != data->token && tmp->type != PIPE)
    {
        if (tmp->type == CMD || (tmp->type == ARG && \
            tmp->prev != data->token->prev && tmp->prev->type > 5))
            count ++;
        tmp = tmp->next;
    }
    return (count);
}
char **get_param(t_data *data, t_token *token)
{
    char **cmd_param;
    int i;
    t_token *tmp;

    i = 0;
    cmd_param = malloc(sizeof(char *) * (count_args(data,token) + 1));
}