/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:19:54 by cassassa          #+#    #+#             */
/*   Updated: 2024/06/28 14:19:57 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**lst_to_arr(t_list *env)
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

//swap to elems in array
static void	ft_swap_str_tab(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

//sorts array
void	sort_array(char **arr, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmpp(arr[i], arr[j], __INT_MAX__);
			if (diff > 0)
			{
				ft_swap_str_tab(i, j, arr);
				continue ;
			}
			j++;
		}
	i++;
	}
}
