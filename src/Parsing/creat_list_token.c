/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:04:27 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 16:14:14 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool add_cmd(t_token **begin, char **command)
{
    
}
bool create_list_token(t_token **begin, char *command)
{
    (*begin) = NULL;
    while (*command)
    {
        while (is_space(*command))
            command++;
        if (*command && !is_special(command) && !add_cmd(begin, &command))
        {
            if (*begin)
                free_token(begin);
            return (false);
        }
        else if (*command && is_special(command) && !add_special(begin, &command))
        {
            if (*begin)
                free_token(begin);
            return (false);
        }
    }
    return (true);
}