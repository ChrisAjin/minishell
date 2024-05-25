/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:24:56 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:24:56 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list	*tail;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tail = ft_lstlast(*head);
	tail->next = new;
}
