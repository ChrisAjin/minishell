/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:04 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:28:04 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	only_spaces(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_spaces(str[i]))
			return (false);
		i += 1;
	}
	return (true);
}
