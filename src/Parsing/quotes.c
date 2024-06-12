/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:10:59 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/12 13:24:10 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void quoting_choice(bool *doubleq, bool *simpleq, int *index, char c)
{
    if ((c == '\'' || c == '"' ) && !*simpleq && !*doubleq)
    {
        if (c == '\'' && !*doubleq)
            *simpleq = true;
        else if (c == '"' && !*simpleq)
            *doubleq = true;
        if (index)
            ++(*index);
    }
    else if ((c == '\'' || c == '"'))
    {
        if (c == '\'' && !*doubleq && *simpleq)
            *simpleq = false;
        else if (c == '"' && !*simpleq && *doubleq)
            *doubleq = false;
        if (index)
            ++(*index);
    }
}

int open_quote(t_data *data, char *line)
{
    bool doubleq;
    bool simpleq;

    int i;

    i = 0;
    doubleq = false;
    simpleq = false;
    while (line && line[i])
    {
        quoting_choice(&doubleq, &simpleq, &i, line[i]);
        if (line[i] && line[i] != '\'' && line[i] != '"')
            ++i;
    }
    if (doubleq || simpleq)
    {
        print_error("open quote\n");
        data->exit_code = 2;
        return (1);
    }
    return (0);
}