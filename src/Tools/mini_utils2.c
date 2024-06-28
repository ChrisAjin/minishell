/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:31:05 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 14:33:47 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**list_to_arr(t_list *env)
{
	t_list	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->str);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->str);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
