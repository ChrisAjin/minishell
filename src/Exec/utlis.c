/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:58:42 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/27 20:02:42 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitest.h"

char	**split_paths(t_list *env)
{
	t_list	*tmp;
	int		i;
	char	**paths;

	tmp = env;
	i = 0;
	paths = NULL;
	if (!env)
		return (paths);
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PATH", 4) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp->str + 5, ':');
	return (paths);
}

