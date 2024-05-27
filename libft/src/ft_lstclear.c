/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:43:03 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 14:43:03 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next;

	next = *lst;
	while (next)
	{
		tmp = next;
		next = next->next;
		(*del)(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
