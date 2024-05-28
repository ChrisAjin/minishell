/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:17:42 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/28 15:43:10 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int add_to_list_token(t_token **list, char *str, int type)
{
    t_token *new;

    if (!token_new_elem(&new, str, type))
        return (0);
    if (!(*list))
        add_first(list, new);
    else
    {
        new->prev = (*list)->prev;
        new->next = (*list);
        (*list)->prev->next = new;
        (*list)->prev = new;
    }
    return (1);
}

void free_token(t_token **list)
{
    t_token *tmp;
    t_token *current;

    if(!(*list))
        return ;
    current = *list;
    while (current->next != *list)
    {
        tmp = current;
        current = current->next;
        free(tmp->str);
        free(tmp);
    }
    free(current->str);
    free(current);
    *list = NULL;
}