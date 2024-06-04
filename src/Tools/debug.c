/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:44:29 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/03 16:18:00 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_token(t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp->next != token)
    {
        printf("Type : %d, [%s]\n", tmp->type, tmp->str);
        tmp = tmp->next;
    }
    printf("Type : %d, [%s]\n", tmp->type, tmp->str);
}